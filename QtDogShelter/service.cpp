#include "service.h"
#include <algorithm>
#include <iostream>
#include "repo_abstract.h"
#include "service.h"

int Service::add_dog(const std::string &name, const std::string &breed, int age, const std::string &image) {
	/*
	* Append a dog to the list.
	* Input: name, breed, image - strings, age - int -> parameters for the new entry (Dog)
	* Output: 0 on success, -2 on failure (duplicates are not allowed)
	*/
	Dog d = Dog(name, breed, age, image);
	if (this->repo.index_of(d) != -1)
		return -2;

	this->repo.add(d);
	return 0;
}

int Service::remove_dog(int index) {
	/*
	* Remove a dog from the list.
	* Input: index in list
	* Output: 0 on success, -1 on invalid index
	*/
	if (index < 0 || index >= this->get_size())
		throw ServiceException("Can't remove at id = " + std::to_string(index) + ".");

	Dog d = repo.get(index);
	repo.remove(d);
	//return this->repo.remove_at(index);
	return 0;
}

int
Service::update_dog(int index, const std::string &name, const std::string &breed, int age, const std::string &image) {
	/*
	* Update a dog from the list.
	* Input: index in list, name, breed, image - strings, age - int -> parameters to be modified
	* Output: 0 on success, -1 on invalid index
	*/
	if (index < 0 || index >= get_size())
		throw ServiceException("Can't update at id = " + std::to_string(index) + ".");

	Dog d = Dog(name, breed, age, image);

	repo.update_at(index, d);
	return 0;
}

int Service::adopt_dog(int index, bool adopted = true) {
	/*
	* Adopt a dog from the list. (Set its adoption flag)
	* Input: index in list, adopted - adoption status
	* Output: n/a
	*/
	auto od = repo.get(index);

	Dog d = Dog(od.get_name(), od.get_breed(), od.get_age(), od.get_image());
	d.set_adopted(adopted);

	repo.update_at(index, d);
	return 0;
}

std::string lowercase(std::string initial) {
	/*
	* HELPER FUNCTION lowercase
	* Returns the lower-case version of a string.
	*/
	std::string final{ std::move(initial) };
	std::transform(final.begin(), final.end(), final.begin(), ::tolower);
	return final;
}

bool DogFilter::operator()(Dog &dog) {
	/*
	* DogFilter's () operator
	* Predicate function that establishes whether a Dog meets the Filter conditions.
	* i.e. dog.breed ~= filter.breed and dog.age >= filter.age
	* Input: reference to Dog object
	* Output: true, if the object meets the filter criteria
	*/
	std::string current_breed(lowercase(dog.get_breed()));
	return (current_breed.find(breed) != std::string::npos) && dog.get_age() >= min_age;
}

std::vector<Dog> Service::filter_dogs(const std::string &breed, int min_age) {
	std::vector<Dog> filtered;
	std::vector<Dog> &dogs = all_dogs();

	/* "G Retriever" becomes "g retriever" */
	std::string by_breed(lowercase(breed));

	/* Initialize a DogFilter */
	auto df = DogFilter(by_breed, min_age);
	std::copy_if(dogs.begin(), dogs.end(), std::back_inserter(filtered), df);

	return filtered;
}

Dog& Service::get_dog_by_name(const std::string & name)
{
	for (auto &dog : all_dogs())
		if (dog.get_name() == name)
			return dog;
	throw ServiceException(std::string("There is no dog with name `" + name + "`."));
}

int Service::adopt_by_name(const std::string &name) {
	/*
	* Adopt by a Dog's name. Sets Dog's adoption status to `true`.
	* Used to sync between a filtered list and the main repository.
	* Input: name - string, a dog's name
	* Output: 0 on success, -1 on failure
	* Exceptions: n/a
	*/
	/*for (auto &dog : all_dogs()) {
		if (dog.get_name() == name) {
			dog.set_adopted(true);
			return 0;
		}
	}*/
	try {
		Dog& dog = get_dog_by_name(name);
		dog.set_adopted(true);
		return 0;
	}
	catch (ServiceException &se) {
		return -1;
	}
}

int Service::unadopt_by_name(const std::string & name)
{
	try {
		Dog& dog = get_dog_by_name(name);
		dog.set_adopted(false);
		return 0;
	}
	catch (ServiceException &se) {
		return -1;
	}
}