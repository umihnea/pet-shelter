#pragma once
#include "redo_ops.h"
#include <memory>

#include <QDebug>

class UndoOp {
protected:
	Repository * repo;
public:
	UndoOp(Repository* m) : repo{ m } {};
	virtual void undo() = 0;
	virtual std::unique_ptr<RedoOp> get_redo() = 0;
	virtual ~UndoOp() = default;
};

class UndoAdd : public UndoOp {
private:
	Dog dog;
	int index;
public:
	UndoAdd(Repository* m, const Dog& d, int i) : UndoOp{ m }, dog{ d }, index(i) {};
	void undo() override;
	std::unique_ptr<RedoOp> get_redo() override;
};

class UndoRemove : public UndoOp {
private:
	Dog copy;
	int index;
public:
	UndoRemove(Repository* m, const Dog& d, int i) : UndoOp{ m }, copy{ d }, index(i) { qDebug() << "Undo got copy: `" << copy.get_name().c_str() << "`."; };
	void undo() override;
	std::unique_ptr<RedoOp> get_redo() override;
};

class UndoUpdate : public UndoOp {
private:
	Dog copy_of_original;
	Dog copy_of_new;
	int index;
public:
	UndoUpdate(Repository* m, const Dog& d, const Dog& nd, int i) : UndoOp{ m }, copy_of_original{ d }, copy_of_new{ nd }, index(i) { qDebug() << "Undo of update got copy: `" << copy_of_original.get_name().c_str() << "`."; };
	void undo() override;
	std::unique_ptr<RedoOp> get_redo() override;
};
