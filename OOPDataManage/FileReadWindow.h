#pragma once
#include <QFileDialog>
#include "ui_FileReadWindow.h"


class FileReadWindow : public QFileDialog
{
    Q_OBJECT

public:
    FileReadWindow(QWidget *parent = nullptr);
    ~FileReadWindow();
    
private:
    Ui::FileReadWindowClass ui;
};
