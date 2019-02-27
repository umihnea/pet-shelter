#include "repo_csv.h"
#include <iostream>
#include <fstream>
#include <windows.h>

#include <QDebug>

void CSVRepo::save() {
	/*
	* Save the repo into a file (given by path).
	* Input: n/a;  Output: n/a
	*/
	std::ofstream g(path);
	if (!g.is_open())
		throw StorageException(std::string("Unable to save in file `" + path + "`.\n"));
	for (const Dog &dog : get_collection()) {
		g << dog << '\n';
		std::cout << dog << '\n';
	}
	g.close();
}

void CSVRepo::load() {
	/*
	* Load the repo from a file (given by path).
	* Input: n/a;  Output: n/a
	*/
	std::ifstream f(this->path);
	if (!f.is_open())
		throw StorageException(std::string("Unable to load from file `" + this->path + "`.\n"));
	Dog dog;
	while (f >> dog) { add(dog); }
	f.close();
}

void CSVRepo::open_in_app() {
	//std::string notepad = "notepad.exe";
	std::string aux = "\"" + path + "\"";
	ShellExecute(nullptr, LPCWSTR("open"), LPCWSTR("notepad.exe"), LPCWSTR(aux.c_str()), nullptr, SW_SHOWNORMAL);
}
