#include "admin_gui.h"
#include "dog_validator.h"
#include <QDebug>
#include <string>
#include <algorithm>

AdminGUI::AdminGUI(Service &s) : service{ s } {
	initialize_components();
	connect_signal_slots();
	load_list(s.all_dogs());
}

void AdminGUI::initialize_components() {
	QHBoxLayout* main_layout = new QHBoxLayout;

	QGroupBox* group_box = new QGroupBox(tr("Shelter List..."));
	QVBoxLayout* left_vbox_layout = new QVBoxLayout;

	cbox = new QComboBox(this);
	cbox->addItem(tr("Compact"));
	cbox->addItem(tr("Detailed"));
	left_vbox_layout->addWidget(cbox);

	dog_list = new QListWidget;
	left_vbox_layout->addWidget(dog_list);


	QLabel* labels[num_line_edits];
	const std::string text_labels[num_line_edits] = { "Name:", "Breed:", "Age:", "Image URL:" };
	for (int i = 0; i < num_line_edits; i++) {
		labels[i] = new QLabel(tr(text_labels[i].c_str()));
		line_edit[i] = new QLineEdit;
		left_vbox_layout->addWidget(labels[i]);
		left_vbox_layout->addWidget(line_edit[i]);
	}

	group_box->setLayout(left_vbox_layout);

	QGroupBox* actions_box = new QGroupBox(tr("Actions..."));
	QVBoxLayout* rigth_vbox_layout = new QVBoxLayout;

	const std::string button_labels[5] = { "Add...", "Remove...", "Update...", "[14] Undo...", "[14] Redo..." };
	for (int i = 0; i < 5; i++) {
		action_button[i] = new QPushButton(tr(button_labels[i].c_str()));
		rigth_vbox_layout->addWidget(action_button[i]);
	}

	actions_box->setLayout(rigth_vbox_layout);

	main_layout->addWidget(group_box);
	main_layout->addWidget(actions_box);
	setLayout(main_layout);
}

void AdminGUI::connect_signal_slots() {
	QObject::connect(action_button[0], &QPushButton::clicked, this, &AdminGUI::gui_add);
	QObject::connect(action_button[1], &QPushButton::clicked, this, &AdminGUI::gui_remove);
	QObject::connect(action_button[2], &QPushButton::clicked, this, &AdminGUI::gui_update);
	QObject::connect(dog_list, &QListWidget::itemSelectionChanged, [&] {
		if (dog_list->selectedItems().isEmpty()) {
			for (int i = 0; i < num_line_edits; i++)
				line_edit[i]->setText("");
			return;
		}
		selected_item = dog_list->selectedItems().at(0);
		display_dog_info();
	});

	/* lab12 activity */
	connect(cbox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [&] (int i) {
		if (i == 0) detailed = false; else detailed = true;
		load_list(service.all_dogs());
	});

	/* lab14 undo+redo */
	connect(action_button[3], &QPushButton::clicked, [&] {
		try { service.undo(); load_list(service.all_dogs()); }
		catch (UndoException &ue) {
			QMessageBox::critical(this, tr("Undo"), QString::fromStdString(ue.what()));
		}
	});

	connect(action_button[4], &QPushButton::clicked, [&] {
		try { service.redo(); load_list(service.all_dogs()); }
		catch (UndoException &ue) {
			QMessageBox::critical(this, tr("Redo"), QString::fromStdString(ue.what()));
		}
	});
}

void AdminGUI::display_dog_info() {
	if (selected_item == nullptr)
		return;

	//std::string dog_name = selected_item->text().toStdString();
	//const Dog& d = service.get_dog_by_name(dog_name);
	int id = selected_item->data(Qt::UserRole).toInt();
	const Dog& d = service.get_dog(id);

	line_edit[0]->setText(QString::fromStdString(d.get_name()));
	line_edit[1]->setText(QString::fromStdString(d.get_breed()));
	line_edit[2]->setText(QString::number(d.get_age()));
	line_edit[3]->setText(QString::fromStdString(d.get_image()));
}

void AdminGUI::load_list(const std::vector<Dog>& dogs) {
	dog_list->clear();
	int id = 0;

	// lab12 activity: compact/detailed
	std::vector<std::string> str_list{};
	if (detailed) {
		for (const Dog& dog : dogs) {
			std::string tag(dog.get_name());
			tag += ", ";
			tag += dog.get_breed();
			tag += ", ";
			tag += std::to_string(dog.get_age());

			str_list.push_back(tag);
		}
	} else {
		for (const Dog& dog : dogs)
			str_list.push_back(dog.get_name());
	}

	for (auto dog_tag : str_list) {
		QListWidgetItem* item =
			new QListWidgetItem(QString::fromStdString(dog_tag), dog_list);

		item->setData(Qt::UserRole, QString::number(id));
		id++;
	}
}

void AdminGUI::gui_remove() {
	if (selected_item == nullptr) {
		QMessageBox::critical(this, "Remove", "No selection.");
		return;
	}

	int id = selected_item->data(Qt::UserRole).toInt();

	try {
		service.remove_dog(id);
		load_list(service.all_dogs());
	}
	catch (ServiceException &se) {
		QMessageBox::warning(this, "Remove Error", QString::fromStdString(se.what()));
	}
}

void AdminGUI::gui_update() {
	if (selected_item == nullptr) {
		QMessageBox::critical(this, "Update", "No selection.");
		return;
	}

	int id = selected_item->data(Qt::UserRole).toInt();

	std::vector<std::string> args = {};
	for (int i = 0; i < num_line_edits; i++) {
		args.push_back(line_edit[i]->text().toStdString());
	}

	int age = -1;
	try { age = std::stoi(args[2]); }
	catch (std::exception &e) { QMessageBox::warning(this, "Update Error", "Age is a positive integer."); }
	if (age == -1) { return; }

	try {
		service.update_dog(id, args[0], args[1], age, args[3]);
		load_list(service.all_dogs());
	}
	catch (ServiceException &se) {
		QMessageBox::warning(this, "Update - Error", QString::fromStdString(se.what()));
	}
	catch (ValidationException &ve) {
		QMessageBox::critical(this, "Update - Validation Exception", ve.what());
	}
}

void AdminGUI::gui_add() {
	std::vector<std::string> args = {};
	for (int i = 0; i < num_line_edits; i++) {
		args.push_back(line_edit[i]->text().toStdString());
		//qDebug() << args[i].c_str();
	}

	int age = -1;
	try { age = std::stoi(args[2]); }
	catch (std::exception &e) { QMessageBox::warning(this, "Warning", "Age is a positive integer."); }
	if (age == -1) { return; }

	try {
		service.add_dog(args[0], args[1], age, args[3]);
		load_list(service.all_dogs());
	}
	catch (ValidationException &ve) {
		QMessageBox::critical(this, "Validation Exception", ve.what());
	}
}



