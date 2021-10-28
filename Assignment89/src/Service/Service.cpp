#include "Service.h"
#include "Event.h"
#include<iostream>
#include<algorithm>
#include "Operation.h"
using namespace std;



int Service::addEvent(const string& title, const string& description, const string& date, const string& time, int participants, const string& link)
{
	Event newEvent{ title, description, date, time, participants, link };
	this->ev.validate(newEvent);
	AddEvent* op = new AddEvent(this->repo, newEvent);
	this->op.execute(op);
	return 0;
}

int Service::removeEvent(const string& title)
{
	Event toBeDeleted = this->repo.findByTitle(title);
	RemoveEvent* op1 = new RemoveEvent(this->repo, toBeDeleted);
	try
	{
		this->userrepo.findByTitle(title);
		RemoveEvent* op2 = new RemoveEvent(this->userrepo, toBeDeleted);
		std::vector<Operation*> ops;
		ops.push_back(op1);
		ops.push_back(op2);
		CascadedOperation* co = new CascadedOperation(ops);
		this->op.execute(co);
	}
	catch (RepoException& re)
	{
		this->op.execute(op1);
	}
	return 0;
}

int Service::updateEvent(const string& title, const string& description, const string& date, const string& time, int participants, const string& link)
{
	this->ev.validate(Event{ title, description,date, time, participants, link });
	Event toBeUpdated = this->repo.findByTitle(title);
	UpdateEvent* op1 = new UpdateEvent(this->repo, toBeUpdated, description, date, time, participants, link);
	try
	{
		this->userrepo.findByTitle(title);
		UpdateEvent* op2 = new UpdateEvent(this->userrepo, toBeUpdated, description, date, time, participants, link);
		std::vector<Operation*> ops;
		ops.push_back(op1);
		ops.push_back(op2);
		CascadedOperation* co = new CascadedOperation(ops);
		this->op.execute(co);

	}
	catch (RepoException& re)
	{
		this->op.execute(op1);
	}
	return 0;
}

std::vector<Event> Service::eventList()
{
	std::vector<Event>eventList = this->repo.getAll();
	return eventList;
}


std::vector<Event> Service::nextEventUserDA(int month)
{
	std::vector<Event> allevents = this->repo.getAll();
	std::vector<Event> events(allevents.size());
	if (month == 0)
	{
		events = allevents;
		sort(events.begin(), events.end(), compare);
		return events;}
	else
	{
		auto it = copy_if(allevents.begin(), allevents.end(), events.begin(), [month](Event& ev) {return ev.getMonth() == month; });
		events.resize(distance(events.begin(), it));
		sort(events.begin(), events.end(), compare);
		return events;}
}

int Service::addEventUser(Event &e)
{
	
	Event e2{ e };
	e2.setParticipants(e.getParticipants() + 1);
	this->userrepo.addEvent(e2);
	this->repo.updateEvent(e, e.getLink(), e.getDescription(), e.getDate(), e.getTime(), e.getParticipants() + 1);
	//AddEvent* op1 = new AddEvent(this->userrepo, e2);
	//UpdateEvent* op2 = new UpdateEvent(this->repo, e, e.getDescription(), e.getDate(), e.getTime(), e.getParticipants()+1, e.getLink());
	//std::vector<Operation*> ops;
	//ops.push_back(op1);
	//ops.push_back(op2);
	//CascadedOperation* co = new CascadedOperation(ops);
	//this->op.execute(co);
	return 0;
}

int Service::removeEventUser(const std::string& name)
{
	Event& toBeDeleted = this->repo.findByTitle(name);
	this->userrepo.removeEvent(toBeDeleted);
	this->repo.updateEvent(toBeDeleted, toBeDeleted.getLink(), toBeDeleted.getDescription(), toBeDeleted.getDate(), toBeDeleted.getTime(), toBeDeleted.getParticipants() -1);
	/*RemoveEvent* op1 = new RemoveEvent(this->userrepo, toBeDeleted);
	UpdateEvent* op2 = new UpdateEvent(this->repo,toBeDeleted, toBeDeleted.getDescription(), toBeDeleted.getDate(), toBeDeleted.getTime(), toBeDeleted.getParticipants()-1, toBeDeleted.getLink());
	std::vector<Operation*> ops;
	ops.push_back(op1);
	ops.push_back(op2);
	CascadedOperation* co = new CascadedOperation(ops);
	this->op.execute(co);*/
	return 0;
}

std::vector<Event> Service::userEventList()
{
	std::vector<Event> eventList = this->userrepo.getAll();
	return eventList;
}

void Service::undo()
{
	this->op.undo();
}

void Service::redo()
{
	this->op.redo();
}

void Service::restart()
{
	this->op.clear();
}
