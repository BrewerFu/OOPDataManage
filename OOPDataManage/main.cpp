#include <QtWidgets/QApplication>
#include"FileManager.h"
#include"GeomertyFile/CFeature.h"
#include"GeometryManager.h"
#include"QtSql/qsqldatabase.h"
#include"QtSql/qsqlquery.h"
#include"QtSql/qsqlerror.h"



int main(int argc, char *argv[])
{

	QApplication a(argc, argv);

	GeometryManager& manager = GeometryManager::GetInstance();

	CGeometry* geo = manager.CreateGeometry(GeometryType::Point);


	return 0;

}


