#pragma once
#include"GeomertyFile/CFeature.h"
#include"DBDriver/DBDriver.h"


struct FeatureSet
{
	std::vector<CFeature> S;
};

class DBManager
{
public:
	DBManager();
	~DBManager();

	bool Connect(DBType type,QString dbname,QString host,QString user,QString password);

	bool DisConnect();

	bool IsConnect();

	bool SaveFeature(CFeature* feature);

	CFeature ReadAllFeature();

	bool DeleteFeature(CFeature* feature);

	bool AlterFeature(CFeature* feature, CFeature* newfeature);

	DBType Drivers();

private:

};



