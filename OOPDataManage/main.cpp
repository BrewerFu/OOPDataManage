#include "FileReadWindow.h"
#include <QtWidgets/QApplication>
#include"FileManager.h"
#include"GeomertyFile/CFeature.h"


int main(int argc, char *argv[])
{
 
    FileManager& manager = FileManager::GetInstance();

    std::string path = "C:/Users/25294/Desktop/Text.txt";
    manager.Open(path);
    CFeature feature(GeometryType::Point);
    CPoint* prt = new CPoint(1, 2);
    feature.AppendGeometry(prt);
    prt = new CPoint(3, 4);
    feature.AppendGeometry(prt);
    manager.Write(&feature);
    manager.Save();
    manager.Close();
    return 0;
}

//QApplication a(argc, argv);
//FileReadWindow w;
//w.show();
//return a.exec();
