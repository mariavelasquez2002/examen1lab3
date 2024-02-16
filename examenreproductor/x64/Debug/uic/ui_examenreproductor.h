/********************************************************************************
** Form generated from reading UI file 'examenreproductor.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXAMENREPRODUCTOR_H
#define UI_EXAMENREPRODUCTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_examenreproductorClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *examenreproductorClass)
    {
        if (examenreproductorClass->objectName().isEmpty())
            examenreproductorClass->setObjectName(QString::fromUtf8("examenreproductorClass"));
        examenreproductorClass->resize(600, 400);
        menuBar = new QMenuBar(examenreproductorClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        examenreproductorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(examenreproductorClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        examenreproductorClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(examenreproductorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        examenreproductorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(examenreproductorClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        examenreproductorClass->setStatusBar(statusBar);

        retranslateUi(examenreproductorClass);

        QMetaObject::connectSlotsByName(examenreproductorClass);
    } // setupUi

    void retranslateUi(QMainWindow *examenreproductorClass)
    {
        examenreproductorClass->setWindowTitle(QApplication::translate("examenreproductorClass", "examenreproductor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class examenreproductorClass: public Ui_examenreproductorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXAMENREPRODUCTOR_H
