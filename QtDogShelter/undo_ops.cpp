#include "undo_ops.h"
#include <QDebug>

/* UndoAdd: */
void UndoAdd::undo() {
	repo->remove_at(index);
	qDebug() << "Undone an add operation";
}

std::unique_ptr<RedoOp> UndoAdd::get_redo() {
	std::unique_ptr<RedoOp> redo = std::make_unique<RedoAdd>(repo, dog);
	return std::move(redo);
}

/* UndoRemove: */
void UndoRemove::undo() {
	repo->add(copy, false);
	qDebug() << "Undone a remove operation - added dog: `" << copy.get_name().c_str() << "`";
}

std::unique_ptr<RedoOp> UndoRemove::get_redo() {
	std::unique_ptr<RedoOp> redo = std::make_unique<RedoRemove>(repo, copy);
	return std::move(redo);
}

/* UndoUpdate: */
void UndoUpdate::undo() {
	repo->update_at(index, copy_of_original, false);
	qDebug() << "Undone a undo operation - restored dog" << copy_of_original.get_name().c_str() << "at position" << index;
}

std::unique_ptr<RedoOp> UndoUpdate::get_redo() {
	std::unique_ptr<RedoOp> redo = std::make_unique<RedoUpdate>(repo, copy_of_original, copy_of_new, index);
	return std::move(redo);
}