#include "repo.h"
#include "dog_validator.h"
#include <qdebug.h>

#include "undo_engine.h"

int Repository::add(const Dog &d, bool register_undo) {
	/*
	* Adds a Dog object to the repository.
	* Input: Dog d
	* Output: 0 on success, -1 if already in the repo
	*/
	if (this->index_of(d) != -1)
		return -1;
	DogValidator::validate(d);
	this->collection.push_back(d);

	if (undo_engine != nullptr && register_undo) {
		std::unique_ptr<UndoOp> add_uop;
		add_uop = std::make_unique<UndoAdd>(this, d, collection.size() - 1);
		undo_engine->register_undo(std::move(add_uop));
	}

	return 0;
}

Dog Repository::remove(const Dog &d, bool register_undo) {
	/*
	* Removes a Dog object from the repository and returns a copy.
	* Input: Dog d
	* Output: cp - a copy of Dog d
	*/
	Dog cp = Dog(d.get_name(), d.get_breed(), d.get_age(), d.get_image());
	int index = this->index_of(d);
	this->remove_at(index);

	if (undo_engine != nullptr && register_undo) {
		std::unique_ptr<UndoOp> remove_uop;
		remove_uop = std::make_unique<UndoRemove>(this, cp, index);
		undo_engine->register_undo(std::move(remove_uop));
	}

	return cp;
}

int Repository::index_of(const Dog &d) {
	/*
	* Returns the index of a Dog object from the repository.
	* Input: Dog d
	* Output: index of d on success, -1 if not found
	*/
	auto it = std::find(collection.begin(), collection.end(), d);
	if (it == collection.end())
		return -1;
	else return static_cast<int>(std::distance(collection.begin(), it));
}

int Repository::remove_at(int index) {
	if (0 <= index && index < collection.size()) {
		collection.erase(collection.begin() + index);
		return 0;
	}
	return -1;
}

Dog Repository::update_at(int index, const Dog &new_d, bool register_undo) {
	/*
	* Updates a Dog at position index. Returns the old object.
	* Input: index, new_d - replacement
	* Output: copy of the old object
	*/
	auto cp = this->collection[index];
	DogValidator::validate(new_d);
	this->collection[index] = new_d;

	if (undo_engine != nullptr && register_undo) {
		std::unique_ptr<UndoOp> update_uop;
		update_uop = std::make_unique<UndoUpdate>(this, cp, new_d, index);
		undo_engine->register_undo(std::move(update_uop));
	}

	return Dog(cp.get_name(), cp.get_breed(), cp.get_age(), cp.get_image());
}

Dog &Repository::get(int index) {
	return this->collection[index];
}