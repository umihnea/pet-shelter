#pragma once
#include <string>

class Dog
{
	std::string name;
	std::string breed;
	int age;
	std::string image;
	bool adopted = false;
public:
	Dog();
	Dog(const std::string &name, const std::string &breed, int age, const std::string &image);
	~Dog();

	std::string get_name() const { return name; };
	std::string get_breed() const { return breed; };
	std::string get_image() const { return image; };
	bool is_adopted() const { return adopted; };
	int get_age() const { return age; };

	void set_name(const std::string &new_name) { name = new_name; };
	void set_breed(const std::string &new_breed) { breed = new_breed; };
	void set_image(const std::string &new_image) { image = new_image; };
	void set_age(int new_age) { age = new_age; };
	void set_adopted(bool flag) { adopted = flag; };

	bool operator==(const Dog &);
	friend std::ostream &operator<<(std::ostream &os, const Dog &d);
	friend std::istream &operator>>(std::istream &is, Dog &d);
};

