#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Skd.h"

class Skd : public QMainWindow
{
    Q_OBJECT

public:
    Skd(QWidget *parent = nullptr);
    ~Skd();

private:
    Ui::SkdClass ui;
};
