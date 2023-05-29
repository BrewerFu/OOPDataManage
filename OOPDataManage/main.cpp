#include "FileReadWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileReadWindow w;
    w.show();
    return a.exec();
}
