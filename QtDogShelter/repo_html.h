#pragma once
#include <utility>
#include "repo_abstract.h"

class HTMLRepo : public StorageRepo {
private:
	std::string html_path;
public:
	explicit HTMLRepo(const std::string &path, std::string html) : StorageRepo{ path }, html_path{ std::move(html) } {}

	void save() override;

	void load() override;

	void open_in_app() override;
};
