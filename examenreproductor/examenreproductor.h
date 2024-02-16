#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_examenreproductor.h"

class examenreproductor : public QMainWindow
{
    Q_OBJECT

public:
    examenreproductor(QWidget *parent = nullptr);
    ~examenreproductor();

private:
    Ui::examenreproductorClass ui;
};
