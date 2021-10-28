
#include "Event.h"
#include <string>
#include <iostream>
#include<sstream>
#include<vector>
using namespace std;


Event::Event(const string& title, const string& description, const string& date, const string& time, int participants, const string& link)
{
	this->title = title;
	this->description = description;
	this->date = date;
	this->time = time;
	this->participants = participants;
	this->link = link;
}

Event::~Event(){
}

Event::Event(const Event& event)
{
	this->title = event.title;
	this->description = event.description;
	this->date = event.date;
	this->time = event.time;
	this->participants = event.participants;
	this->link = event.link;
}

int Event::getDay() 
{
	unsigned int endpos = this->date.find_first_of(".");
	int day = stoi(this->date.substr(0, endpos));
	return day;

}

int Event::getMonth()
{
	unsigned int startpos = this->date.find_first_of(".");
	unsigned int endpos = this->date.find_last_of(".");
	return stoi(this->date.substr(startpos+1, endpos));
}

int Event::getYear()
{
	unsigned int startpos = this->date.find_last_of(".");
	return stoi(this->date.substr(startpos+1));
}

int Event::getHour()
{
	unsigned int endpos = this->time.find_first_of(":");
	int hour = stoi(this->time.substr(0, endpos));
	return hour;
}

int Event::getMinute()
{
	unsigned int endpos = this->time.find_first_of(":");
	int minute = stoi(this->time.substr(endpos+1));
	return minute;
}

void Event::setTitle(const string& title)
{
	this->title = title;
}

void Event::setDescription(const string& description)
{
	this->description = description;
}

void Event::setDate(const string& date)
{
	this->date = date;
}

void Event::setTime(const string& time)
{
	this->time = time;
}
void Event::setParticipants(int participants)
{
	this->participants = participants;
}

void Event::setLink(const string& link) {
	this->link = link;
}

bool Event::operator==(const Event& event)
{
	if (this->title == event.title)
		return true;
	return false;
}

string Event::toString()
{	stringstream txt;
	txt << "Title: " << this->title << ", Description: " << this->description << ", Date: " << this->date << ", Time: " << this->time << ", Participants: " << this->participants<< ", Link: " << this->link << endl;
	return txt.str();}

std::ostream& operator<<(std::ostream& os, const Event& e)
{
	os << e.title << "," << e.description << "," << e.date << "," << e.time <<","<< e.participants <<"," << e.link;
	return os;
}

vector<string> tokenize(string str, char delimiter)
{
	vector<string> result;
	stringstream ss(str);
	string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);
	return result;
}

std::istream& operator>>(std::istream& is, Event& e)
{
	string line;
	getline(is, line);

	vector<string> tokens = tokenize(line, ',');
	if (tokens.size() != 6)
		return is;
	e.title = tokens[0];
	e.description = tokens[1];
	e.date = tokens[2];
	e.time = tokens[3];
	e.participants = stoi(tokens[4]);
	e.link = tokens[5];
	return is;
}

bool compare(Event e1, Event e2)
{
	if (e1.getYear() > e2.getYear())
		return false;
	else if (e1.getYear() < e2.getYear())
		return true;
	else if (e1.getYear() == e2.getYear())
	{
		if (e1.getMonth() > e2.getMonth())
			return false;
		else if (e1.getMonth() < e2.getMonth())
			return true;
		else if (e1.getMonth() == e2.getMonth())
		{
			if (e1.getDay() > e2.getDay())
				return false;
			else if (e1.getDay() < e2.getDay())
				return true;
			else if (e1.getDay() == e2.getDay())
			{
				if (e1.getHour() > e2.getHour())
					return false;
				else if (e1.getHour() < e2.getHour())
					return true;
				else if (e1.getHour() == e2.getHour())
				{
					if (e1.getMinute() > e2.getMinute())
						return false;
					else if (e1.getMinute() < e2.getMinute())
						return true;
					else if (e1.getMinute() == e2.getMinute())
						return false;
				}
			}
		}
	}
}