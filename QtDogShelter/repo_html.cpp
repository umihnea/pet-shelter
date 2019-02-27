#include "repo_html.h"

#include <iostream>
#include <fstream>
#include <windows.h>

std::string td(const Dog &dog) {
	return std::string("<tr><td>" + dog.get_name() + "</td><td>" + dog.get_breed() + "</td><td>" +
		std::to_string(dog.get_age()) + "</td><td><a href='" + dog.get_image() +
		"'>pic</a></td><td>" + (dog.is_adopted() ? "yes" : "no") + "</td></tr>");
}

void HTMLRepo::save() {
	/*
	* Save the repo into a HTML file (given by html_path).
	* Input: n/a;  Output: n/a
	*/
	std::ofstream g(html_path);
	if (!g.is_open())
		throw StorageException(std::string("Unable to save in file `" + html_path + "`.\n"));

	g << "<!DOCTYPE html><html><head><title>Adoption List</title>"
		"</head><body><h3>Pets</h3><hr/><table border='1'>";

	g << "<tr><td>Name</td><td>Breed</td><td>Age (months)</td><td>Image Link</td><td>Adopted</td></tr>";

	for (const Dog &dog : get_collection())
		g << td(dog) << '\n';

	g << "</table></body></html>";

	g.close();
}

void HTMLRepo::load() {
	/*
	* Load the repo from a CSV file (given by path).
	* Input: n/a;  Output: n/a
	*/
	std::ifstream f(path);
	if (!f.is_open())
		throw StorageException(std::string("Unable to load from file `" + path + "`.\n"));
	Dog dog;
	while (f >> dog) {
		add(dog);
	}
}

void HTMLRepo::open_in_app() {
	std::string chrome = R"(C:\Program Files (x86)\Google\Chrome\Application\chrome.exe)";
	std::string aux = "\"" + html_path + "\"";
	//ShellExecute(nullptr, "open", chrome.c_str(), aux.c_str(), nullptr, SW_SHOWNORMAL);
}
