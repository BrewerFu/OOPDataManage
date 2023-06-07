#pragma once
#include<qstring.h>
#include<qsqldatabase.h>
#include<qsqlquery.h>
#include<qsqlerror.h>
#include<qsqlrecord.h>
#include"../GeomertyFile/CFeature.h"
#include"../GeomertyFile/CPolyGon.h"
#include"../GeomertyFile/CPolyLine.h"
#include"../GeomertyFile/CRectAngle.h"
#include"../GeomertyFile/CSection.h"

class DBSql;

//数据库枚举类型
enum DBType
{
    MYSQL,
	SQLITE,
	POSTGRESQL,
	ORACLE,
	SQLSERVER,
	ACCESS,
	DB2,
	SYBASE,
	INFORMIX,
	OTHER
};

//数据库驱动抽象类
class DBDriver
{

public:
    DBDriver():m_sql(nullptr){};
    virtual~DBDriver() {};

    virtual bool Connect(QString dbname,QString host,QString user,QString password) = 0;

    virtual void DisConnect() = 0;

    virtual bool IsConnect() = 0;

    virtual bool InsertFeature(CFeature* feature) = 0;

    virtual CFeature* ReadFeature(int DBID) = 0;

    virtual bool DeleteFeature(CFeature* feature) = 0;

    virtual QVector<int> ReadFeatureID() = 0;

protected:
    QSqlDatabase m_database;
    DBSql* m_sql;
};

//数据库解码类
class DBSqlCoder
{
public:
    DBSqlCoder() {};
    ~DBSqlCoder() {};

    virtual QStringList Decode(QString& text,QString delimiter)const;

    virtual QString Encode(QStringList& list,QString delimiter)const;

};

//数据库SQL类，负责执行与封装SQL语句
class DBSql
{
public:
    bool exec();
    bool setDataBase(QSqlDatabase database);
    bool prepare(QString sql);
    void bindValue(QString name, QVariant value);
    void bindValue(int pos, QVariant value);
    QVariant value(int pos);
    QVariant value(QString name);
    QSqlError lastError();
    bool next();

    virtual int InsertFeature(CFeature* feature);

    virtual int ExistFeature(CFeature* feature);

    virtual int SaveFeature(CFeature* feature);

    virtual CFeature* ReadFeature(int DBID);

    virtual bool DeleteFeature(CFeature* feature);

protected:
    bool AddReference(std::shared_ptr<CGeometry> geo);

    virtual int InsertFeature(CFeature* feature,int ID);

    virtual void BindAttribute(std::shared_ptr<CGeometry> geo);

    virtual void PhraseAttribute(std::shared_ptr<CGeometry> geo);

    virtual int InsertPoint(std::shared_ptr<CPoint> point);

    virtual int InsertPath(std::shared_ptr<CPath> path);

    virtual int InsertPolyLine(std::shared_ptr<CPolyLine> polyline);

    virtual int InsertRing(std::shared_ptr<CRing> ring);

    virtual int InsertPolyGon(std::shared_ptr<CPolyGon> polygon);

    virtual int InsertRectAngle(std::shared_ptr<CRectAngle> rectangle);

    virtual int InsertCircle(std::shared_ptr<CCircle> circle);

    virtual int InsertSection(std::shared_ptr<CSection> section);

    virtual bool ReadPoint(std::shared_ptr<CPoint>& point, int DBID);

    virtual bool ReadPath(std::shared_ptr<CPath>& path, int DBID);

    virtual bool ReadPolyLine(std::shared_ptr<CPolyLine>& line, int DBID);

    virtual bool ReadRing(std::shared_ptr<CRing>& ring, int DBID);

    virtual bool ReadPolyGon(std::shared_ptr<CPolyGon>& Gon, int DBID);

    virtual bool ReadRectAngle(std::shared_ptr<CRectAngle>& rect, int DBID);

    virtual bool ReadCircle(std::shared_ptr<CCircle>& circle, int DBID);

    virtual bool ReadSection(std::shared_ptr<CSection>& section, int DBID);

    virtual int ExistPoint(std::shared_ptr<CPoint> point);

    virtual int ExistPath(std::shared_ptr<CPath> path);

    virtual int ExistRing(std::shared_ptr<CRing> ring);

    virtual int ExistPolyLine(std::shared_ptr<CPolyLine> polyline);

    virtual int ExistPolyGon(std::shared_ptr<CPolyGon> polygon);

    virtual int ExistRectAngle(std::shared_ptr<CRectAngle> rectangle);

    virtual int ExistCircle(std::shared_ptr<CCircle> circle);

    virtual int ExistSection(std::shared_ptr<CSection> section);

    DBSqlCoder m_coder;
    QSqlQuery m_Sql;
};

