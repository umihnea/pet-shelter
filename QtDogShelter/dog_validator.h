#pragma once

#include "dog.h"

class DogValidator {
public:
	DogValidator::DogValidator() {};

	DogValidator::~DogValidator() {};

	static void validate(const Dog &d);
};

class ValidationException : public std::exception {
	std::string message;
public:
	ValidationException(std::string _msg) : message(_msg) {};

	const char *what() const noexcept override;
};

