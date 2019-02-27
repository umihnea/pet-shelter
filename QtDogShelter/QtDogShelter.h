#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtDogShelter.h"

class QtDogShelter : public QMainWindow
{
	Q_OBJECT

public:
	QtDogShelter(QWidget *parent = Q_NULLPTR);

private:
	Ui::QtDogShelterClass ui;
};
