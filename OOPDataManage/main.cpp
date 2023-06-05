#include "FileReadWindow.h"
#include <QtWidgets/QApplication>
#include"FileManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileReadWindow w;
    w.show();
    return a.exec();
}


