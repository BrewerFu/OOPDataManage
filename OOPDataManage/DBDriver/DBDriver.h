#pragma once
#include"../GeomertyFile/CFeature.h"
#include<qstring.h>
#include<qsqldatabase.h>
#include<qsqlquery.h>
#include<qsqlerror.h>
#include"../GeomertyFile/CPolyGon.h"
#include"../GeomertyFile/CRectAngle.h"
#include"../GeomertyFile/CSection.h"


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

class DBDriver
{

public:
    DBDriver();
    ~DBDriver();

    virtual bool Connect(QString host,QString user,QString password,QString dbname) = 0;

    virtual bool DisConnect() = 0;

    virtual bool IsConnect() = 0;

    virtual bool SaveFeature(CFeature* feature) = 0;

    virtual CFeature ReadFeature() = 0;

    virtual bool DeleteFeature(CFeature* feature) = 0;

    virtual bool AlterFeature(CFeature* feature, CFeature* newfeature) = 0;

    virtual bool IsExist(CFeature* feature) = 0;

private:
    QSqlDatabase m_database;
};

class DBSql
{
    bool exec();
    bool setDataBase(QSqlDatabase database);

protected:
    QSqlQuery m_Sql;
};

class DBSqlCoder
{
public:
    DBSqlCoder() {};
	~DBSqlCoder() {};

    void setText(QString text) { m_text = text; };
    void setText(QStringList list) { m_list = list; };

    virtual QStringList DecodeStyle(CGeometry* geo);

    virtual bool EncodeStyle(CGeometry* geo);

    virtual QStringList Decode();

    virtual QString Encode();

protected:
    QString m_text;
    QStringList m_list;
};

class DBSqlAdd:public DBSql
{
public:
    DBSqlAdd() {};
    ~DBSqlAdd() {};

    virtual bool AddPoint(std::shared_ptr<CPoint> point,int ID,int featureID);

    virtual bool AddPath(std::shared_ptr<CPath> path,int featureID);

    virtual bool AddPolyLine(std::shared_ptr<CPolyLine> polyline,int featureID);

    virtual bool AddRing(std::shared_ptr<CRing> ring,int featureID);

    virtual bool AddPolyGon(std::shared_ptr<CPolyGon> polygon,int featureID);

    virtual bool AddRectAngle(std::shared_ptr<CRectAngle> rectangle,int featureID);

    virtual bool AddCircle(std::shared_ptr<CCircle> circle,int featureID);

    virtual bool AddSection(std::shared_ptr<CSection> section,int featureID);

protected:
    virtual bool BindAttribute(std::shared_ptr<CGeometry> geo);
    DBSqlCoder m_coder;
};