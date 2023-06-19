#include "DBManager.h"

DBManager::DBManager()
{
	driver = nullptr;
}

DBManager::~DBManager()
{
	delete driver;
}

bool DBManager::Connect(DBType type, QString dbname, QString host, QString user, QString password)
{
	switch (type)
	{
	case SQLITE:
		driver = new SQLiteDriver();
		break;
	default:
		return false;
	}
	return driver->Connect(dbname, host, user, password);
}

void DBManager::DisConnect()
{
	driver->DisConnect();
}

bool DBManager::IsConnect()
{
	return driver->IsConnect();
}

bool DBManager::SaveFeature(CFeature* feature)
{
	return driver->InsertFeature(feature);
}

bool DBManager::DeleteFeature(CFeature* feature)
{
	return driver->DeleteFeature(feature);
}


QVector<int> DBManager::ReadFeatureID()
{
	return driver->ReadFeatureID();
}

CFeature* DBManager::ReadFeature(int DBID)
{
	return driver->ReadFeature(DBID);
}