#pragma once
#include "Operation.h"

class OperationManager
{
private:
	std::vector<Operation*> undoStack;
	std::vector<Operation*> redoStack;
public:
	void execute(Operation* op);
	void undo();
	void redo();
	void clear();

};

class OperationException : public std::exception
{
	const char* msg;
public:
	OperationException(const char* msg) : msg{ msg } {}
	const char* what() const throw() { return this->msg; }
};
