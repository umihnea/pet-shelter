/********************************************************************************
** Form generated from reading UI file 'QtDogShelter.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTDOGSHELTER_H
#define UI_QTDOGSHELTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtDogShelterClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtDogShelterClass)
    {
        if (QtDogShelterClass->objectName().isEmpty())
            QtDogShelterClass->setObjectName(QStringLiteral("QtDogShelterClass"));
        QtDogShelterClass->resize(600, 400);
        menuBar = new QMenuBar(QtDogShelterClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        QtDogShelterClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtDogShelterClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtDogShelterClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtDogShelterClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QtDogShelterClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtDogShelterClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtDogShelterClass->setStatusBar(statusBar);

        retranslateUi(QtDogShelterClass);

        QMetaObject::connectSlotsByName(QtDogShelterClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtDogShelterClass)
    {
        QtDogShelterClass->setWindowTitle(QApplication::translate("QtDogShelterClass", "QtDogShelter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtDogShelterClass: public Ui_QtDogShelterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTDOGSHELTER_H
