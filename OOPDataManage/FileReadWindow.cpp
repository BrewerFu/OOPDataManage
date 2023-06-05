#include "FileReadWindow.h"

FileReadWindow::FileReadWindow(QWidget *parent)
    : QFileDialog(parent)
{
    ui.setupUi(this);
}

FileReadWindow::~FileReadWindow()
{
}
