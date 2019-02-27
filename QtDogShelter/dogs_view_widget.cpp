#include "dogs_view_widget.h"

DogsViewWidget::DogsViewWidget(StorageRepo & r, QAbstractItemModel * m) : repo{ r }, table_model{ m } {
	draw_gui();
	table_view->setModel(table_model);
	table_view->setSortingEnabled(true);
}

void DogsViewWidget::draw_gui() {
	QVBoxLayout* main_layout = new QVBoxLayout;
	QHBoxLayout* hbox = new QHBoxLayout;

	table_view = new QTableView;
	table_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	hbox->addWidget(table_view);
	main_layout->addLayout(hbox);
	setLayout(main_layout);
}


