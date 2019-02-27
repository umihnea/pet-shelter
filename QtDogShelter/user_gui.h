#pragma once
#include "service.h"
#include "dog.h"
#include <QtWidgets>
#include <QLineEdit>

class UserGUI : public QWidget {
	Q_OBJECT

public:
	UserGUI(Service &s);

private:
	Service & service;
	std::vector<Dog> filtered;
	int current = 0;

	QLineEdit* line_edit[4];
	QPushButton* btn_prev;
	QPushButton* btn_adopt;
	QPushButton* btn_next;

	void initialize_gui();
	void connect_slots();
	void pop_filter_dialog();
	int load_current_dog();

public slots:
	void next_dog();
	void previous_dog();
	void adopt_disadopt();

};

