#pragma once

#include <string>

class CustomException {
	std::string message;
public:
	explicit CustomException(std::string _msg) : message(_msg) {};
	std::string what() const { return message; }
};

