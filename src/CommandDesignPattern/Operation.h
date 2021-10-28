#pragma once
#include "Repository.h"

class Operation
{
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
	virtual void redo() = 0;
};

class CascadedOperation : public Operation
{
private:
	std::vector<Operation*> ops;
public:
	CascadedOperation(std::vector<Operation*> ops) : ops{ ops }{}
	void execute() override;
	void undo() override;
	void redo() override;

};

class AddEvent : public Operation
{
public:
	Repository& repo;
	Event e;
	AddEvent(Repository& repo, Event e) :repo{ repo }, e{ e }{}
	void execute() override;
	void undo() override;
	void redo() override;
};

class RemoveEvent : public Operation
{
public:
	Repository& repo;
	Event e;
	RemoveEvent(Repository& repo, Event& e) : repo{ repo }, e{ e }{}
	void execute();
	void undo();
	void redo();
};

class UpdateEvent : public Operation
{
public:
	Repository& repo;
	Event e;
	std::string description;
	std::string date;
	std::string time;
	int participants;
	std::string link;
	UpdateEvent(Repository& repo, Event e, std::string description, std::string date, std::string time, int participants, std::string link) :repo{ repo }, e{ e }, description{ description }, date{ date }, time{ time }, participants{ participants }, link{ link }{}
	void execute();
	void undo();
	void redo();
};