#pragma once

#include "repo.h"

/*
* Prototype class for all Persistent Storage Repositories.
*/
class StorageRepo : public Repository {
protected:
	std::string path;

public:
	StorageRepo(const std::string &path);

	virtual ~StorageRepo() {}

	virtual void save() = 0;

	virtual void load() = 0;

	virtual void open_in_app() = 0;
};

class StorageException : public std::exception {
	std::string message;
public:
	explicit StorageException(std::string _msg) : message(std::move(_msg)) {};
	const char *what() const noexcept override;
};
