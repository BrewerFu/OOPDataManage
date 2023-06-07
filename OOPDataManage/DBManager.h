#define DBMANAGER_EXPORTS

#pragma once
#include"GeomertyFile/CFeature.h"
#include"DBDriver/SQLiteDriver.h"

#ifdef DBMANAGER_EXPORTS
#define DBMANAGER_API __declspec(dllexport)
#else
#define DBMANAGER_API __declspec(dllimport)
#endif // DBMANAGER_EXPORTS

//数据库管理器，单例
class DBManager
{
public:
	//单例模式
	static DBManager& GetInstance()
	{
		static DBManager instance;
		return instance;
	}

	bool Connect(DBType type,QString dbname,QString host=NULL,QString user=NULL,QString password=NULL);

	void DisConnect();

	bool IsConnect();

	bool SaveFeature(CFeature* feature);

	bool DeleteFeature(CFeature* feature);

	QVector<int> ReadFeatureID();

	CFeature* ReadFeature(int DBID);

private:
	DBDriver *driver;
	DBManager();
	~DBManager();
};



