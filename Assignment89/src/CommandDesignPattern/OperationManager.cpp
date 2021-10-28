#include "OperationManager.h"

void OperationManager::execute(Operation* op)
{
	op->execute();
	this->undoStack.push_back(op);
}

void OperationManager::undo()
{
	if (this->undoStack.size() == 0)
		throw OperationException{ "No more undos!" };
	Operation* last_executed = this->undoStack[this->undoStack.size() - 1];
	last_executed->undo();
	this->redoStack.push_back(last_executed);
	this->undoStack.pop_back();
}

void OperationManager::redo()
{
	if (this->redoStack.size() == 0)
		throw OperationException{ "No more redos!" };
	Operation* last_executed = this->redoStack[this->redoStack.size() - 1];
	last_executed->redo();
	this->undoStack.push_back(last_executed);
	this->redoStack.pop_back();
}

void OperationManager::clear()
{
	this->undoStack.clear();
	this->redoStack.clear();
}


