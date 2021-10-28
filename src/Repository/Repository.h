#pragma once
#include "Event.h"
#include <vector>
#include<exception>

class Repository 
{
protected:
	std::vector<Event> events;

public:
	Repository();
	//Constructor for repository objects 
	
	virtual bool addEvent(Event& e);
	// Adds a new event to the repository
	// Input: an event instance
	// Output: true if the event was added, false if it is already in the repository

	virtual bool removeEvent(Event& e);
	// Removes an event from the repository
	// Input: an event instance
	// Output: true if the event was removed, false if it was not in the repository to begin with

	virtual bool updateEvent(Event& e, const std::string& link, const std::string& description, const std::string& date, const std::string& time, int participants);
	// Updates an event from the repository
	// Input: an country instance, a new link, description, date, time and participants
	// Output: true if the event was updated, false if it was not in the repository
    
    virtual Event& findByTitle(const std::string& title);
	//Retrieves an event instance based on its title
	//Input: a given title
	//Output: the event instance having the given title, an instance initialized with empty fields otherwise
	
	virtual int len();
	//Number of the events in the repository
	
	virtual std::vector<Event>getAll();
	//Returns a copy of the list of elements in the repository

};

void populateRepository(Repository& repo);

class RepoException : public std::exception 
{
	const char* msg;
public:
	RepoException(const char* msg): msg{msg} {}
	const char* what() const throw() { return this->msg; }
};