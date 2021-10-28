#pragma once
#include <string>
#include<iostream>

class Event 
{
private:
	std::string title;
	std::string description;
	std::string date;
	std::string time;
	int participants;
	std::string link;


public:
	Event() :title{ "" }, description{ "" }, date{ "" }, time{ "" },participants{0}, link{""}{}

	Event(const std::string& title, const std::string& description,const std::string& date, const std::string& time, int participants,const std::string& link);
	
	Event(const Event& event);

	bool  operator==(const Event& e);

	~Event();

	const std::string& getTitle() const { return this->title; }
	const std::string& getDescription() const { return this->description; }
	const std::string& getDate() const { return this->date; }
	const std::string& getTime() const { return this->time; }
	int getParticipants() const { return this->participants; }
	const std::string& getLink() const { return this->link; }
	int getDay();
	int getMonth();
	int getYear();
	int getHour();
	int getMinute();
	void setTitle(const std::string& title);
	void setDescription(const std::string& description);
	void setDate(const std::string& date);
	void setTime(const std::string& time);
	void setParticipants(int participants);
	void setLink(const std::string& link);
	std::string toString();
	friend std::ostream& operator<<(std::ostream&, const Event&);
	friend std::istream& operator>>(std::istream&, Event&);
};

bool compare(Event e1, Event e2);