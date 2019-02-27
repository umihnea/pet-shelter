#pragma once
#include <utility>
#include "repo_abstract.h"
#include "undo_engine.h"

#include <qdebug.h>

class Service {
	StorageRepo &repo;
	UndoEngine &undo_engine;

public:
	Service(StorageRepo &_r, UndoEngine &ue) : repo(_r), undo_engine(ue) {
		try { repo.load(); } catch (StorageException &e) { qDebug() << e.what(); }
	}

	~Service() {
		//try { repo.save(); } catch (StorageException &e) { qDebug() << e.what(); } 
	};

	int add_dog(const std::string &name, const std::string &breed, int age, const std::string &image);

	int remove_dog(int);

	int update_dog(int, const std::string &name, const std::string &breed, int age, const std::string &image);

	int adopt_dog(int, bool);

	int adopt_by_name(const std::string &name);

	int unadopt_by_name(const std::string &name); // sister function, reason: so that test code stays the same

	std::vector<Dog> filter_dogs(const std::string &, int); 

	int get_size() const { return repo.get_size(); }

	Dog &get_dog(int index) { return repo.get(index); }

	Dog &get_dog_by_name(const std::string& name);

	std::vector<Dog> &all_dogs() { return repo.get_collection(); }

	/* lab14 undo + redo */
	void undo() { undo_engine.undo();  };
	void redo() { undo_engine.redo();  };
};

class DogFilter {
private:
	int min_age;
	std::string breed;
public:
	DogFilter(std::string _b, int _a) : breed(std::move(_b)), min_age(_a) {}

	bool operator()(Dog &);
};

class ServiceException : public std::exception {
	std::string message;
public:
	ServiceException(std::string _msg) : message(_msg) {};
	const char *what() const noexcept override {
		return message.c_str();
	};
};