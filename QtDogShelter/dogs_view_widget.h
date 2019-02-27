#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QAbstractItemModel>
#include "repo_abstract.h"

class DogsViewWidget : public QWidget {
	Q_OBJECT

private:
	StorageRepo & repo;
	QAbstractItemModel* table_model;
	QTableView* table_view = nullptr;

public:
	explicit DogsViewWidget(StorageRepo &r, QAbstractItemModel* m);
	~DogsViewWidget() {}

private:
	void draw_gui();

};

