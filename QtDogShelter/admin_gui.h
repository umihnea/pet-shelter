#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qlineedit.h>
#include <QtWidgets>
#include "service.h"
#include "dogs_view_widget.h"

#define num_line_edits 4

class AdminGUI : public QWidget {
	Q_OBJECT

private:
	Service & service;
	QLineEdit* line_edit[num_line_edits];
	QListWidget* dog_list;
	QPushButton* action_button[5];
	QListWidgetItem* selected_item = nullptr;

	QComboBox* cbox;
	bool detailed = false;

public:
	AdminGUI(Service &s);
	void initialize_components();
	void connect_signal_slots();
	void load_list(const std::vector<Dog>&);

	void display_dog_info();

public slots:
	void gui_add();
	void gui_remove();
	void gui_update();
};

