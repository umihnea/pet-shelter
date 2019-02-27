#include <iostream>
#include <cstring>
#include <assert.h>
#include <QDebug>

#include "test.h"
#include "dog.h"
#include "dog_validator.h"
#include "repo.h"
#include "repo_csv.h"
#include "service.h"

using namespace std;

void test_all() {
	qDebug() << "* Running all tests:";
	test_dog();
	test_dog_validator();
	test_repo();
	test_polymorphic_repo();
	test_service();
	qDebug() << "* Finished all tests.";
}

void test_dog() {
	qDebug() << "\t* Testing domain object...";

	Dog* shawn = new Dog();
	shawn->set_name("Shawn");
	shawn->set_breed("Golden Retriever");
	shawn->set_age(15);
	shawn->set_image("www.dogs.com/shawn");
	assert(shawn->get_age() == 15);
	assert(shawn->get_name() == "Shawn");
	assert(shawn->get_image() == "www.dogs.com/shawn");
	assert(shawn->get_breed() == "Golden Retriever");
	delete shawn;

	Dog *furball = new Dog("Furball", "Poodle", 12, "www.dogs.com/furball");
	assert(furball->get_age() == 12);
	assert(furball->get_name() == "Furball");
	assert(furball->get_image() == "www.dogs.com/furball");
	assert(furball->get_breed() == "Poodle");
	delete furball;

	qDebug() << "\t* Object tests finished ...";
}

void test_dog_validator()
{
	qDebug() << "\t* Testing object validator...";
	try {
		DogValidator::validate(Dog("non-capitalized", "breed", 10, "link"));
		assert(false);
	}
	catch (const ValidationException &ve) {
		assert(strcmp(ve.what(), "A dog's name must start with a capital letter.\n") == 0);
	}
	try {
		DogValidator::validate(Dog("", "breed", 10, "link"));
		assert(false);
	}
	catch (const ValidationException &ve) {
		assert(strcmp(ve.what(), "A dog's name cannot be less than 2 characters.\n"
			"A dog's name must start with a capital letter.\n") == 0);
	}
	try {
		DogValidator::validate(Dog("Valid", "", 10, "link"));
		assert(false);
	}
	catch (const ValidationException &ve) {
		assert(strcmp(ve.what(), "A dog's breed cannot be less than 2 characters.\n") == 0);
	}
	qDebug() << "\t* Validator tests finished...";
}

void test_repo()
{
	qDebug() << "\t* Testing repository...";

	Repository r;
	auto dumpling = Dog("Dumpling", "G Shepherd", 10, "link0");
	r.add(dumpling);

	r.add(Dog("Schnapps", "G Retriever", 11, "link1"));
	r.add(Dog("Rosarita", "Poodle", 13, "link2"));
	r.add(Dog("Seneca", "Dobermann", 8, "link3"));
	r.add(Dog("Felix", "Husky", 9, "link4"));

	assert(r.get_size() == 5);

	Dog removed = r.remove(dumpling);
	assert(r.get_size() == 4);
	assert(removed.get_name() == "Dumpling");

	r.update_at(0, Dog("Pudding", "Poodle", 14, "another_link"));
	assert(r.get(0).get_name() == "Pudding");

	qDebug() << "\t* Repository tests finished...";
}

void test_polymorphic_repo()
{
	qDebug() << "\t* Testing storage repository...";

	CSVRepo r("csv_storage_test.csv");
	UndoEngine ue(r);
	Service s(r, ue);

	assert(s.add_dog("Schnapps", "Dachshund", 5, "link1") == 0);
	assert(s.add_dog("Mulberry", "Boxer", 8, "link2") == 0);
	assert(s.add_dog("Pookie", "Pomeranian", 9, "link3") == 0);
	assert(s.add_dog("Snooks", "Pointer", 7, "link4") == 0);
	r.save();

	int sz = s.get_size();
	for (; sz; sz--)
		s.remove_dog(0);

	r.load();
	assert(s.get_size() == 4);
	assert(s.get_dog(0).get_name() == "Schnapps");
	assert(s.get_dog(1).get_breed() == "Boxer");
	assert(s.get_dog(2).get_age() == 9);
	assert(s.get_dog(3).get_image() == "link4");

	qDebug() << "\t* Storage test finished...";
}

void test_service()
{
	qDebug() << "\t* Testing service layer...";
	CSVRepo r("service-test.csv");
	UndoEngine ue(r);
	Service s(r, ue);

	s.add_dog("Schnapps", "Dachshund", 5, "l0");
	s.add_dog("Mulberry", "Boxer", 8, "l1");
	s.add_dog("Pookie", "Pomeranian", 9, "l2");
	s.add_dog("Snooks", "Pointer", 7, "l3");
	assert(s.get_size() == 4);

	s.update_dog(0, "Tuna", "G Shepherd", 4, "other");
	assert(s.get_dog(0).get_name() == "Tuna");

	s.remove_dog(2); // removed Pookie
	assert(s.get_size() == 3);

	s.adopt_dog(0, true);
	s.adopt_dog(2, true);
	assert(s.get_dog(0).is_adopted());
	assert(s.get_dog(2).is_adopted());

	qDebug() << "Service filter:";
	for (auto x : s.filter_dogs("po", 0)) {
		qDebug() << x.get_name().c_str();
	}

	qDebug() << "\t* Service tests finished...";
}