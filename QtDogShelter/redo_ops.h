#pragma once
#include "repo.h"

class RedoOp {
protected:
	Repository * repo;
public:
	RedoOp(Repository* m) : repo{ m } {};
	virtual void redo() = 0;
	virtual ~RedoOp() = default;
};

class RedoAdd : public RedoOp {
private:
	Dog dog;
public:
	RedoAdd(Repository* m, const Dog& d) : RedoOp{ m }, dog{ d } {};
	void redo() override;
};

class RedoRemove : public RedoOp {
private:
	Dog copy;
public:
	RedoRemove(Repository* m, const Dog& d) : RedoOp{ m }, copy{ d } {};
	void redo() override;
};

class RedoUpdate : public RedoOp {
private:
	Dog copy_of_original;
	Dog copy_of_new;
	int index;
public:
	RedoUpdate(Repository* m, const Dog& d, const Dog& nd, int i) : RedoOp{ m }, copy_of_original{ d }, copy_of_new{ nd }, index{ i } {};
	void redo() override;
};