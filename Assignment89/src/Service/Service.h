#pragma once
#include "Repository.h"
#include "EventValidator.h"
#include "OperationManager.h"
#include <vector>
class Service {
private:
	Repository& repo;
	Repository& userrepo;
	EventValidator& ev;
	OperationManager& op;

public:
	Service(Repository& repo, Repository& userrepo, EventValidator& ev, OperationManager& op) :repo{ repo }, userrepo{ userrepo }, ev{ ev }, op{ op }{}
	//Constructor for Service objects
	
	int addEvent(const std::string& title, const std::string& description, const std::string& date, const std::string& time, int participants, const std::string& link);
	// Creates a new event instance and adds it to the repository that is currently managed
	// Input: the title, description, date, time, numbeer of participants and link needed to create an Event instance
	// Output:
	// 0 if the operation was successful
	// Throws exceptions in case the event failed the validation test or was already in the repository
	
	int removeEvent(const std::string& title);
	// Removes an event instance from the repository currently managed 
	// Input: the title of the event to be deleted
	// Output:
	// 0 if the operation was successful
	// Throws an exception if the event was not in the repository

	int updateEvent(const std::string& title, const std::string& description, const std::string& date, const std::string& time, int participants, const std::string& link);
	//Updates an event instance from the repository currently managed
	//Input: the title of the event to be updated, the new description, date, time, number of participants and link
	//Output:
	// 0 if the operation was successful
	// Throws exceptions if the new parameters needed to create an an event were invalid or the event was not in the repository

	
	std::vector<Event> eventList();
	// Gives access to the list of entities from the repository
	// Output: A deep copy of the list of events in the repository

	std::vector<Event> nextEventUserDA(int month);
	// Lists the events in a given month ordered chronologically
	// Input: a month. If none is given, all events in the database are considered
	// Output: A sorted dynamic vector containing the events

	int addEventUser(Event& e);
	// Adds a new event to the user's list of events to attend
	// Input: An event already present in the admin's database
	// Output: 0 is the operation was successful

	int removeEventUser(const std::string& name);
	// Removes an event from the user's list of events to attend
	// Input: the name of the event
	// Output: 0 if the operation was succesful
	// Throws an exception if the event was not in the list

	std::vector<Event> userEventList();
	// Returns a copy to the list of events that the user currently wants to attend

	int adminEventsSize() { return this->repo.len(); }
	int userEventsSize() { return this->userrepo.len(); }
	void undo();
	void redo();
	void restart();
};
