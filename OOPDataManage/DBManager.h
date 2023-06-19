#pragma once
#include"GeomertyFile/CFeature.h"
#include"DBDriver/SQLiteDriver.h"

struct FeatureIDSet
{
	std::vector<int> id;
};

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



