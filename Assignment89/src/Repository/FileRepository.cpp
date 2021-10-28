#include "FileRepository.h"
#include <iostream>
#include<fstream>
#include<algorithm>

void FileRepository::load()
{
	std::ifstream f(this->filename);
	if (! f.is_open())
	{
		return;
	}
	this->events.clear();
	Event e;
	while (f >> e)
	{
		this->events.push_back(e);
	}
	f.close();
}

void FileRepository::save()
{
	std::ofstream f(this->filename);
	if (f.is_open())
	{
		std::for_each(this->events.begin(), this->events.end(), [&f](const auto& x) {f << x << "\n"; });
	}
	f.close();
}

Event& FileRepository::findByTitle(const std::string& title)
{
	this->load();
	return Repository::findByTitle(title);

}

bool FileRepository::addEvent(Event& e)
{
	this->load();
	Repository::addEvent(e);
	this->save();
	return true;
}

bool FileRepository::removeEvent(Event& e)
{
	this->load();
	Repository::removeEvent(e);
	this->save();
	return true;
}

bool FileRepository::updateEvent(Event& e, const std::string& link, const std::string& description, const std::string& date, const std::string& time, int participants)
{
	this->load();
	Repository::updateEvent(e, link, description, date, time, participants);
	this->save();
	return true;
}

int FileRepository::len()
{
	this->load();
	return Repository::len();
}

std::vector<Event> FileRepository::getAll()
{
	this->load();
	return Repository::getAll();
}

