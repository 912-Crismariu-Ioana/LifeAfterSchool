#pragma once
#include"Event.h"
class EventValidator {
public:
	int validate(Event e);
};

class ValidatorException : public std::exception {
	const char* msg;
public:
	ValidatorException(const char* msg) : msg{ msg } {}
	const char* what() const throw() { return this->msg; }
};