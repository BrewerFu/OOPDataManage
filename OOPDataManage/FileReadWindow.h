#pragma once
#include <QtWidgets/QWidget>
#include "ui_FileReadWindow.h"
#include<qbrush.h>

class FileReadWindow : public QWidget
{
    Q_OBJECT

public:
    FileReadWindow(QWidget *parent = nullptr);
    ~FileReadWindow();
    
private:
    Ui::FileReadWindowClass ui;
};
