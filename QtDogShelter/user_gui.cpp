#include "user_gui.h"
#include <QInputDialog>
#include <QFormLayout>
#include <QDebug>

UserGUI::UserGUI(Service &s) : service{ s } {
	pop_filter_dialog();
	initialize_gui();
	connect_slots();
	load_current_dog();
}

void UserGUI::initialize_gui() {
	QVBoxLayout* main_layout = new QVBoxLayout;

	for (int i = 0; i < 4; i++) {
		line_edit[i] = new QLineEdit(this);
		line_edit[i]->setDisabled(true);
	}

	QFormLayout *formbox = new QFormLayout;
	formbox->addRow(tr("Dog's &Name:"), line_edit[0]);
	formbox->addRow(tr("Dog's &Breed:"), line_edit[1]);
	formbox->addRow(tr("Dog's &Age:"), line_edit[2]);
	formbox->addRow(tr("Dog's &Picture:"), line_edit[3]);

	QHBoxLayout* vbox = new QHBoxLayout;
	btn_prev = new QPushButton(tr("<< &Prev"));
	btn_adopt = new QPushButton(tr("&Adopt"));
	btn_next = new QPushButton(tr("&Next >>"));
	vbox->addWidget(btn_prev);
	vbox->addWidget(btn_adopt);
	vbox->addWidget(btn_next);

	main_layout->addLayout(formbox);
	main_layout->addLayout(vbox);

	setLayout(main_layout);
}

void UserGUI::pop_filter_dialog() {
	std::string breed_filter = "";
	int age_filter = 0;

	age_filter = QInputDialog::getInt(this, tr("Age Filter"), tr("Minimum age:"), 0, 0, 100, 1);
	QString raw_breed_filter = QInputDialog::getText(this, tr("Breed Filter"), tr("Breed:"));
	breed_filter = raw_breed_filter.toStdString();

	filtered = this->service.filter_dogs(breed_filter, age_filter);

	if (filtered.size() == 0) {
		QMessageBox::critical(this, tr("Filter Error"), tr("No matches found!"));
		exit(EXIT_FAILURE); //QApplication::exit();
	}
}

void UserGUI::connect_slots() {
	connect(btn_next, &QPushButton::clicked, this, &UserGUI::next_dog);
	connect(btn_prev, &QPushButton::clicked, this, &UserGUI::previous_dog);
	connect(btn_adopt, &QPushButton::clicked, this, &UserGUI::adopt_disadopt);
}

int UserGUI::load_current_dog() {
	if (current <= 0 && current > filtered.size())
		return -1;

	Dog dog = filtered.at(current);
	line_edit[0]->setText(QString::fromStdString(dog.get_name()));
	line_edit[1]->setText(QString::fromStdString(dog.get_breed()));
	line_edit[2]->setText(QString::number(dog.get_age()));
	line_edit[3]->setText(QString::fromStdString(dog.get_image()));

	if (dog.is_adopted())
		btn_adopt->setText("Un-adopt");
	else
		btn_adopt->setText("Adopt");

	return 0;
}

void UserGUI::next_dog() {
	int N = static_cast<int>(filtered.size());
	current = (current + 1) % N;
	load_current_dog();
}

void UserGUI::previous_dog() {
	int N = static_cast<int>(filtered.size());
	if (current == 0) {
		current = N - 1;
	}
	else {
		current--;
	}
	load_current_dog();
}

void UserGUI::adopt_disadopt() {
	Dog dog = filtered.at(current);
	if (!dog.is_adopted()) {
		service.adopt_by_name(dog.get_name());
		filtered[current].set_adopted(true);
		btn_adopt->setText("Un-adopt");
	}
	else {
		service.unadopt_by_name(dog.get_name());
		filtered[current].set_adopted(false);
		btn_adopt->setText("Adopt");
	}
}