#include "undo_engine.h"

void UndoEngine::undo() {
	if (undo_ops.size() == 0) {
		throw UndoException("No undo operations left.");
		return;
	}

	auto lpo = std::move(undo_ops.back());
	undo_ops.pop_back();

	lpo->undo();
	register_redo(std::move(lpo->get_redo()));
}

void UndoEngine::register_undo(std::unique_ptr<UndoOp> op) {
	this->undo_ops.push_back(std::move(op));
}

void UndoEngine::redo() {
	if (redo_ops.size() == 0) {
		throw UndoException("No redo operations left.");
		return;
	}

	auto luo = std::move(redo_ops.back());
	redo_ops.pop_back();

	luo->redo(); /* the undo op will be registered by
				 the repo method called in by the redo function */
}

void UndoEngine::register_redo(std::unique_ptr<RedoOp> op) {
	this->redo_ops.push_back(std::move(op));
}