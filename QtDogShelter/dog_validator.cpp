#include "dog_validator.h"

const char *ValidationException::what() const noexcept {
	return message.c_str();
}

void DogValidator::validate(const Dog &d) {
	std::string errors;
	if (d.get_name().size() < 3)
		errors += std::string("A dog's name cannot be less than 2 characters.\n");
	if (!isupper(d.get_name()[0]))
		errors += std::string("A dog's name must start with a capital letter.\n");
	if (d.get_breed().size() < 3)
		errors += std::string("A dog's breed cannot be less than 2 characters.\n");
	if (d.get_age() <= 0)
		errors += std::string("A dog's age cannot be less than 0.\n");
	if (!errors.empty())
		throw ValidationException(errors);
}

