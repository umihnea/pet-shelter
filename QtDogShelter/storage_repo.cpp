#include "repo_abstract.h"

const char *StorageException::what() const noexcept {
	return message.c_str();
}

StorageRepo::StorageRepo(const std::string &path) {
	this->path = path;
}