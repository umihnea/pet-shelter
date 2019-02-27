#include "redo_ops.h"
#include <QDebug>

void RedoAdd::redo() {
	repo->add(dog);
	qDebug() << "Redone an add.";
}

void RedoRemove::redo() {
	repo->remove(copy);
	qDebug() << "Redone a remove.";
}

void RedoUpdate::redo() {
	repo->update_at(index, copy_of_new);
	qDebug() << "Redone an update.";
}
