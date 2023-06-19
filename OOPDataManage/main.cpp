#include <QtWidgets/QApplication>
#include"FileManager.h"
#include"DBManager.h"
#include"GeomertyFile/CFeature.h"
#include"GeometryManager.h"
#include"GeomertyFile/CPolyGon.h"
#include"DBDriver/DBDriver.h"
#include<qvariant.h>
#include"QtSql/qsqldatabase.h"
#include"QtSql/qsqlquery.h"
#include"QtSql/qsqlerror.h"



int main(int argc, char *argv[])
{

	QApplication a(argc, argv);
	//CREATE_GEOSHARED_PTR(CPolyLine, line);
	//
	//CREATE_GEOSHARED_PTR(CPath, path);

	//CREATE_GEOSHARED_PTR(CPoint, p1, 1, 2);
	//CREATE_GEOSHARED_PTR(CPoint, p2, 3, 4);

	//path->AppendPoint(p1);
	//path->AppendPoint(p2);
	//line->AppendPath(path);

	FileManager& fm = FileManager::GetInstance();
	CFeatureManager& fm1 = CFeatureManager::GetInstance();
	DBManager& dbm = DBManager::GetInstance();


	//CFeature* f1 = fm1.CreateFeature(GeometryType::PolyLine);
	//f1->AppendGeometry(line);

	dbm.Connect(DBType::SQLITE, "sqlite.db");

	CFeature* fe =  dbm.ReadFeature(1);

	dbm.DeleteFeature(fe);

	fm.Open("D:\\test.txt");
	return 0;
}


