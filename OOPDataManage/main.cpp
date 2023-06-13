#include <QtWidgets/QApplication>
#include"FileManager.h"
#include"GeomertyFile/CFeature.h"
#include"QtSql/qsqldatabase.h"
#include"QtSql/qsqlquery.h"
#include"QtSql/qsqlerror.h"



int main(int argc, char *argv[])
{

	QApplication a(argc, argv);

    QSqlDatabase database;

    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        // 建立和SQlite数据库的连接
        database = QSqlDatabase::addDatabase("QSQLITE");
        // 设置数据库文件的名字
        database.setDatabaseName("sqlite.db");
    }
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        QSqlQuery sql_query(database);
        sql_query.exec("SELECT * FROM Point");
        while (sql_query.next())
        {
            qDebug() << sql_query.value(0);
            qDebug() << sql_query.value(1);
            qDebug() << sql_query.value(2);
        }
    }

}


