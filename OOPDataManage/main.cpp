#include <QtWidgets/QApplication>
#include"FileManager.h"
#include"GeomertyFile/CFeature.h"
#include"GeometryManager.h"
#include"GeomertyFile/CPolyGon.h"
#include"QtSql/qsqldatabase.h"
#include"QtSql/qsqlquery.h"
#include"QtSql/qsqlerror.h"



int main(int argc, char *argv[])
{

	QApplication a(argc, argv);
	CFeatureManager& manager = CFeatureManager::GetInstance();
	FileManager& fileManager = FileManager::GetInstance();
	CFeature* feature = manager.CreateFeature(GeometryType::Point);

	CREATE_GEOSHARED_PTR(CPoint, point,1,2);
	CREATE_GEOSHARED_PTR(CPoint, point1, 2, 3);
	CREATE_GEOSHARED_PTR(CPoint, point2, 3, 4);
	feature->AppendGeometry(point);
	feature->AppendGeometry(point1);
	feature->AppendGeometry(point2);
	fileManager.Open("D:\\test.txt");
	fileManager.Write(feature);
	fileManager.Close();

	return 0;

}


