#pragma once

#include "Repository.h"

#include <string>
class FileRepository : public Repository
{
protected:
	std::string filename;
	void load();
    virtual void save();
	
public:
	FileRepository(const std::string& filename) :filename{ filename }, Repository(){this->load(); }

	bool addEvent(Event& e) override;
	// Adds a new event to the repository
	// Input: an event instance
	// Output: true if the event was added, false if it is already in the repository

	bool removeEvent(Event& e) override;
	// Removes an event from the repository
	// Input: an event instance
	// Output: true if the event was removed, false if it was not in the repository to begin with

	bool updateEvent(Event& e, const std::string& link, const std::string& description, const std::string& date, const std::string& time, int participants) override;
	// Updates an event from the repository
	// Input: an country instance, a new link, description, date, time and participants
	// Output: true if the event was updated, false if it was not in the repository

	Event& findByTitle(const std::string& title) override;
	//Retrieves an event instance based on its title
	//Input: a given title
	//Output: the event instance having the given title, an instance initialized with empty fields otherwise

	int len() override;
	//Number of the events in the repository

	std::vector<Event>getAll() override;
	//Returns a copy of the list of elements in the repository

};