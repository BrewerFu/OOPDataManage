#include"SQLiteDriver.h"

SQLiteDriver::SQLiteDriver()
{
	m_database=QSqlDatabase::addDatabase("QSQLITE"); 
	m_sql = new DBSql();
}

SQLiteDriver::~SQLiteDriver()
{
	m_database.close(); 
	delete m_sql;
}

bool SQLiteDriver::Connect(QString dbname,QString host, QString user, QString password)
{
	m_database.setDatabaseName(dbname);
	m_database.setHostName(host);
	m_database.setUserName(user);
	m_database.setPassword(password);

	if (m_database.open())
		return true;
	else
	{
		qDebug() << "Error:" << m_database.lastError();
		throw m_database.lastError();
		return false;
	}
}

void SQLiteDriver::DisConnect()
{
	m_database.close();
}

bool SQLiteDriver::IsConnect()
{
	return m_database.isOpen();
}

bool SQLiteDriver::InsertFeature(CFeature* feature)
{
	if(m_sql->InsertFeature(feature))
		return true;
	else 
		return false;
}

CFeature* SQLiteDriver::ReadFeature(int DBID)
{
	return m_sql->ReadFeature(DBID);
}

bool SQLiteDriver::DeleteFeature(CFeature* feature)
{
	if (m_sql->DeleteFeature(feature))
		return true;
	else
		return false;
}

QVector<int> SQLiteDriver::ReadFeatureID()
{
	m_sql->prepare("SELECT DBID FROM Feature");
	m_sql->exec();
	QVector<int> result;
	while (m_sql->next())
	{
		result.push_back(m_sql->value(0).toInt());
	}
	return result;
}
