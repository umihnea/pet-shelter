#pragma once
#include "repo_abstract.h"
#include "undo_ops.h"
#include "redo_ops.h"

class UndoEngine {
private:
	StorageRepo & repo;
	std::vector<std::unique_ptr<UndoOp> > undo_ops{};
	std::vector<std::unique_ptr<RedoOp> > redo_ops{};
public:
	UndoEngine(StorageRepo &r) : repo{ r } {};
	void undo();
	void redo();
	void register_undo(std::unique_ptr<UndoOp>);
	void register_redo(std::unique_ptr<RedoOp>);
};

class UndoException : public std::exception {
	std::string message;
public:
	explicit UndoException(std::string _msg) : message(std::move(_msg)) {};
	const char *what() const noexcept override {
		return message.c_str();
	};
};