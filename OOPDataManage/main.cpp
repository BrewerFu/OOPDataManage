#include "FileReadWindow.h"
#include <QtWidgets/QApplication>
#include"FileManager.h"

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    FileReadWindow w;
//    w.show();
//    return a.exec();
//}

int main(int argc, char *argv[])
{
	//TextReader reader;
	//reader.Open("C:/Users/25294/Desktop/Text.txt");
	//GeometryType type =  reader.GetType();
	//CPolyLine geo;
	//while (reader.isNext())
	//{
	//	reader.GetGeometry(geo);
	//}
	//return 0;
	FileManager manager;
	manager.Open("C:/Users/25294/Desktop/Text.txt");
	manager.Read();

	return 0;
}

