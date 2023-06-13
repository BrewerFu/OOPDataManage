#pragma once
#include"DBDriver.h"



class SQLiteDriver : public DBDriver
{
public:
	SQLiteDriver();
	~SQLiteDriver();

	bool Connect(QString host, QString user, QString password, QString dbname) override;

	bool DisConnect() override;

	bool IsConnect() override;

	bool SaveFeature(CFeature* feature) override;

	CFeature ReadFeature() override;

	bool DeleteFeature(CFeature* feature) override;

	bool AlterFeature(CFeature* feature, CFeature* newfeature) override;

	bool IsExist(CFeature* feature) override;

};

