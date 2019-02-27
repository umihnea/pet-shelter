#pragma once

#include "dog.h"
#include "custom_exception.h"

#include <vector>
#include <algorithm>
#include <memory>

class UndoEngine; /* Forward declaration to fix circular dependecy problem. */

class Repository {

	std::vector<Dog> collection;
	UndoEngine* undo_engine = nullptr;

public:

	Repository() = default;

	int add(const Dog &, bool register_undo = true);

	Dog remove(const Dog &, bool register_undo = true);

	int remove_at(int);

	Dog update_at(int, const Dog &, bool register_undo = true);

	Dog &get(int);

	int index_of(const Dog &);

	int get_size() const { return static_cast<int>(collection.size()); }

	std::vector<Dog>& get_collection() { return collection; }

	void set_undo(UndoEngine* ue) { undo_engine = ue; }
};