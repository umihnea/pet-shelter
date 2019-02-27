#pragma once

#include <repo_abstract.h>

class CSVRepo : public StorageRepo
{
public:
	explicit CSVRepo(const std::string &path) : StorageRepo(path) {}

	void save() override;

	void load() override;

	void open_in_app() override;
};

