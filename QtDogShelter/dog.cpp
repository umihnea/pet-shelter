#include "dog.h"
#include <sstream>
#include <vector>
#include <string>

Dog::Dog() : name(""), breed(""), age(0), image("") {}

Dog::Dog(std::string const &name, std::string const &breed, int age, std::string const &image) {
	this->name = name;
	this->breed = breed;
	this->age = age;
	this->image = image;
}

Dog::~Dog() {}

bool Dog::operator==(const Dog &other) {
	return (this->get_name() == other.get_name() && this->get_age() == other.get_age());
}

std::ostream &operator<<(std::ostream &os, const Dog &d) {
	os << d.name << ',' << d.breed << ',' << d.age << ',' << d.image << ',' << (int)d.is_adopted();
	return os;
}

std::vector<std::string> split(const char *str, char c) {
	std::vector <std::string> result;
	do {
		const char *begin = str;
		while (*str != c && *str)
			str++;
		result.emplace_back(std::string(begin, str));
	} while (0 != *str++);
	return result;
}

std::istream &operator>>(std::istream &is, Dog &d) {
	std::string line;
	getline(is, line);
	std::vector<std::string> tokens = split(line.c_str(), ',');

	if (tokens.size() != 5)
		return is;

	d.set_name(tokens[0]);
	d.set_breed(tokens[1]);
	int age = std::stoi(tokens[2]);
	d.set_age(age);
	d.set_image(tokens[3]);
	d.set_adopted(!(tokens[4] == "0"));

	return is;
}
