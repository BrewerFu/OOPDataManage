#pragma once
#include"DBDriver.h"

class SQLiteDriver : public DBDriver
{
public:
	SQLiteDriver();
	~SQLiteDriver();

	bool Connect(QString dbname,QString host, QString user, QString password) override;

	void DisConnect() override;

	bool IsConnect() override;

	bool InsertFeature(CFeature* feature) override;

	CFeature* ReadFeature(int DBID) override;

	bool DeleteFeature(CFeature* feature) override;

	QVector<int> ReadFeatureID() override;
};

