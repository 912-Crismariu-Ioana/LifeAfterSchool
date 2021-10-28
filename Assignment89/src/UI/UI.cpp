#include "UI.h"
#include <iostream>
#include<Windows.h>
#include<shellapi.h>
#include<vector>
using namespace std;



void UI::addEventUI() {
	cout << "Enter the title of the event: " << endl;
	string title, description, date, time, participants, link;
	getline(cin, title);
	cout << "Enter a description of the event: " << endl;
	getline(cin, description);
	cout << "Enter the date: " << endl;
	getline(cin, date);
	cout << "Enter the time: " << endl;
	getline(cin, time);
	cout << "Enter the number of participants: " << endl;
	getline(cin, participants);
	try {
		int parts = stoi(participants);
		cout << "Enter the link to the webpage of the event: " << endl;
		getline(cin, link);
		this->service.addEvent(title, description, date, time, parts, link);
	}
	catch (const std::invalid_argument& ia)
	{
		cout << "Invalid number of participants" << endl;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
	

}

void UI::removeEventUI()
{
	string title;
	cout << "Enter the title of the event that you want to remove: " << endl;
	getline(cin, title);
	try {
		this->service.removeEvent(title);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}

void UI::updateEventUI()
{
	cout << "Enter the title of the event: " << endl;
	string title, description, date, time, participants, link;
	getline(cin, title);
	cout << "Enter a new description for the event: " << endl;
	getline(cin, description);
	cout << "Enter a new date: " << endl;
	getline(cin, date);
	cout << "Enter a new time: " << endl;
	getline(cin, time);
	cout << "Enter a new number of participants: " << endl;
	getline(cin, participants);
	try {
		int parts = stoi(participants);
		cout << "Enter a new link to the webpage of the event: " << endl;
		getline(cin, link);
		this->service.updateEvent(title, description, date, time, parts, link);
	}
	catch (const std::invalid_argument& ia)
	{
		cout << "Invalid number of participants!" << endl;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
	

}

void UI::menuAdmin() {
	bool done = false;
	while (!done) 
	{
		cout << endl;
		cout << "Choose one of the following" << endl;
		cout << "1.Add a new event" << endl;
		cout << "2.Remove an event" << endl;
		cout << "3.Update an event" << endl;
		cout << "4.Display all events in the database" << endl;
		cout << "5.Exit" << endl;
		string input;
		getline(cin, input);
		if (input == "1")
			this->addEventUI();
		else if (input == "2")
			this->removeEventUI();
		else if (input == "3")
			this->updateEventUI();
		else if (input == "4")
		{
			vector<Event> eventList = this->service.eventList();
			for (Event& e : eventList)
			{
				cout << e.toString() << endl;
			}
			cout << endl;
		}
		else if (input == "5")
		{
			cout << "Exiting..." << endl;
			cout << endl;
			done = true;
		}
		else
			cout << "Bad input!" << endl;

	}
	

}



void UI::nextUserEventUIDA()
{
	string month;
	cout << "Enter a month: " << endl;
	getline(cin, month);
	int imonth;
	if (month == "")
		imonth = 0;
	else
	{
		try
		{
			imonth = stoi(month);
		}
		catch (const std::invalid_argument& ia)
		{
			cout << "Invalid month" << endl;
			return;
		}
	}
    vector < Event > events = this->service.nextEventUserDA(imonth);
	bool done = false;
	auto it = events.begin();
	string input;

	while (!done)
	{
		if (it == events.end())
			it = events.begin();
		Event current = *it;
		std::cout << current.toString();
		ShellExecuteA(NULL, "open", current.getLink().c_str(), NULL, NULL, SW_SHOWNORMAL);
		cout << "+ Add event to your list" << endl;
		cout << "> Move on to the next event" << endl;;
		cout << "X Exit" << endl;;
		getline(cin, input);
		if (input == "+")
		{
			try {
				this->service.addEventUser(current);
			}
			catch (const std::exception& e)
			{
				cerr << e.what() << endl;
			}
			it++;
		}
		else if (input == ">")
		{
			it++;
		}
		else if (input == "X")
			done = true;
		else
		{
			cout << "Bad input" << endl;
		}

	}
}


void UI::removeUserEventUI()
{
	string name;
	cout << "Enter the name of the event you want to remove: ";
	getline(cin, name);
	try {
		this->service.removeEventUser(name);
	}
	catch (const std::exception& e)
	{
		cerr << e.what() <<endl;
	}
}

void UI::menuUser() {
	bool done = false;
	while (!done)
	{
		cout << endl;
		cout << "Choose one of the following" << endl;
		cout << "1.See events for a given month" << endl;
		cout << "2.Remove an event from personal list" << endl;
		cout << "3.See personal list of events " << endl;
		cout << "4.Exit" << endl;
		string input;
		getline(cin, input);
		if (input == "1")
			this->nextUserEventUIDA();
		else if (input == "2")
			this->removeUserEventUI();
		else if (input == "3")
		{
			vector<Event> eventList = this->service.userEventList();
			for (Event& e : eventList)
			{
				cout << e.toString() << endl;
			}
			cout << endl;
		}
		else if (input == "4")
		{
			cout << "Exiting..." << endl;
			cout << endl;
			done = true;
		}
		else
			cout << "Bad input!" << endl;

	}

}

void UI::start() {
	bool done = false;
	while (!done)
	{
		cout << " Life After School " << endl;
		cout << "Choose one of the following: " << endl;
		cout << "Admin mode" << endl;
		cout << "User mode" << endl;
		cout << endl;
		string input;
		getline(cin, input);
		if (input == "admin")
			this->menuAdmin();
		else if (input == "user")
			this->menuUser();
		else
			done = true;
	}
	
}