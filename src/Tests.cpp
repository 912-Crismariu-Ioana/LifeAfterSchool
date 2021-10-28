#include "Tests.h"
#include "Event.h"
#include "EventValidator.h"
#include "Repository.h"
#include "Service.h"
#include <assert.h>
#include <exception>
#include<iostream>
#include "OperationManager.h"



void Tests::testDomainGetters()
{
	std::string title = "Football match";
	std::string description = "Match organized by the football team of the university";
	std::string date = "22.03.2020";
	std::string time = "14:30";
	std::string link = "www.football.com";
	Event e1{ title, description, date, time, 0, link };
	assert(title == e1.getTitle());
	assert(description == e1.getDescription());
	assert(date == e1.getDate());
	assert(time ==  e1.getTime());
	assert(link == e1.getLink());
	assert(0 == e1.getParticipants());
	assert(e1.getDay() == 22);
	assert(e1.getMonth() == 3);
	assert(e1.getYear() == 2020);
	assert(e1.getMinute() == 30);
	assert(e1.getHour() == 14);
	//Make a copy
	Event e2(e1);
	assert(e2.getTitle() == "Football match");
	assert(e2.getDescription() == "Match organized by the football team of the university");
	assert(e2.getDate() == "22.03.2020");
	assert(e2.getTime() == "14:30");
	assert(e2.getParticipants() == 0);
	assert(e2.getLink() == "www.football.com");
	assert(compare(e1, e2) == false);


}

void Tests::testDomainSetters()
{
	Event e1{ "Football match", "Match organized by the football team of the university", "22.03.2020", "14:30", 0, "www.football.com" };
	Event e2 = e1;
	e1.setLink("Football competition");
	e1.setDescription("Match organized by the local football team");
	e1.setParticipants(30);
	e1.setDate("25.03.2020");
	e1.setTime("15:15");
	assert(e1.getTitle() == "Football match");
	assert(e1.getDescription() == "Match organized by the local football team");
	assert(e1.getDate() == "25.03.2020");
	assert(e1.getTime() == "15:15");
	assert(e1.getParticipants() == 30);
	assert(e1.getLink() == "Football competition");
	assert(compare(e2, e1) == true);
	assert(compare(e1, Event{ "Football match", "Match organized by the football team of the university", "22.03.2019", "14:30", 0, "www.football.com" }) == false);
	assert(compare(e1, Event{ "Football match", "Match organized by the football team of the university", "22.03.2021", "14:30", 0, "www.football.com" }) == true);
	assert(compare(e1, Event{ "Football match", "Match organized by the football team of the university", "22.02.2020", "14:30", 0, "www.football.com" }) == false);
	assert(compare(e1, Event{ "Football match", "Match organized by the football team of the university", "22.04.2020", "14:30", 0, "www.football.com" }) == true);
	assert(compare(e1, Event{ "Football match", "Match organized by the football team of the university", "26.03.2020", "14:30", 0, "www.football.com" }) == true);
	assert(compare(e1, Event{ "Football match", "Match organized by the football team of the university", "25.03.2020", "14:30", 0, "www.football.com" }) == false);
	assert(compare(e1, Event{ "Football match", "Match organized by the football team of the university", "24.03.2020", "14:30", 0, "www.football.com" }) == false);
	assert(compare(e1, Event{ "Football match", "Match organized by the football team of the university", "25.03.2020", "16:30", 0, "www.football.com" }) == true);
	assert(compare(e1, Event{ "Football match", "Match organized by the football team of the university", "25.03.2020", "15:45", 0, "www.football.com" }) == true);
	assert(compare(e1, Event{ "Football match", "Match organized by the football team of the university", "25.03.2020", "15:00", 0, "www.football.com" }) == false);
	assert(e1.toString() == "Title: Football match, Description: Match organized by the local football team, Date: 25.03.2020, Time: 15:15, Participants: 30, Link: Football competition\n");
}

void Tests::testValidator() {
	EventValidator ev;
	try {
		ev.validate(Event("", "", "", "", 0, ""));}
	catch (ValidatorException ve) {}
	try {
		ev.validate(Event("fjcjg", "gccjc", "hkckh", "iyi", 16, "gyfi.fv"));}
	catch (ValidatorException ve) {}
	try {
		ev.validate(Event("fjcjg", "gccjc", "12.12.2012", "iyi", 16, "gyfi.fv"));}
	catch (ValidatorException ve) {}
	try {
		ev.validate(Event("fjcjg", "gccjc", "12.12.2020", "12:12", 16, "gyfifv"));}
	catch (ValidatorException ve) {}
	try {
		ev.validate(Event("fjcjg", "gccjc", "12.69.2020", "12:12", 16, "gyfif.v"));}
	catch (ValidatorException ve) {}
	try {
		ev.validate(Event("fjcjg", "gccjc", "56.12.2020", "12:12", 16, "gyfi.fv"));}
	catch (ValidatorException ve) {}
	try {
		ev.validate(Event("fjcjg", "gccjc", "12.12.2020", "34:12", 16, "gyfi.fv"));}
	catch (ValidatorException ve) {}
	try {
		ev.validate(Event("fjcjg", "gccjc", "12.12.2020", "12:60", 16, "gyfi.fv"));}
	catch (ValidatorException ve) {}
	try {
		ev.validate(Event("fjcjg", "gccjc", "giy.vi.ihv", "12:12", 16, "gyfi.fv"));}
	catch (ValidatorException ve) {}
	try {
		ev.validate(Event("fjcjg", "gccjc", "12.12.2020", "gcgi:iyiv", 16, "gyfi.fv"));}
	catch (ValidatorException ve) {}
	ev.validate(Event("fjcjg", "gccjc", "12.12.2020", "12:12", 16, "gyfi.fv"));
	try {
		ev.validate(Event("fjcjg", "gccjc", "12.12.2020", "12:iyiv", 16, "gyfi.fv"));}
	catch (ValidatorException ve) {}
	try {
		ev.validate(Event("fjcjg", "gccjc", "yi.12.2020", "12:12", 16, "gyfi.fv"));}
	catch (ValidatorException ve) {}
	try {
		ev.validate(Event("fjcjg", "gccjc", "12.uo.2020", "12:12", 16, "gyfi.fv"));}
	catch (ValidatorException ve) {}
	try {
		ev.validate(Event("fjcjg", "gccjc", "12.12.ugk", "12:12", 16, "gyfi.fv"));}
	catch (ValidatorException ve) {}
	try {
		ev.validate(Event("fjcjg", "gccjc", "12.12.2020", "12:12", 0, "gyfi.fv"));}
	catch (ValidatorException ve) {}
}

void Tests::testAddRepo()
{
	Repository repo1;
	Repository repo2;
	repo2 = repo1;
	Event ev = Event("fjcjg", "gccjc", "12.12.2020", "12:12", 15, "gyfi.fv");
	repo1.addEvent(ev);
	try {
		repo1.addEvent(ev);
	}
	catch(RepoException re) {}
	assert(repo2.addEvent(ev) == true);
	assert(repo1.len() == 1);
	assert(repo2.len() == 1);
	std::vector<Event>events = repo1.getAll();
	assert(events.size() == 1);
	assert(events[0].getTitle() == "fjcjg");
	populateRepository(repo1);
	assert(repo1.len() == 11);
	assert(repo2.len() == 1);
}

void Tests::testRemoveRepo()
{
	Repository repo1;
	Event e = Event("fjcjg", "gccjc", "12.12.2020", "12:12", 15, "gyfi.fv");
	try {
		repo1.removeEvent(e);
	}
	catch (RepoException re) {}
	repo1.addEvent(e);
	assert(repo1.removeEvent(e) == true);
	assert(repo1.len() == 0);
}

void Tests::testUpdateRepo()
{
	Repository repo1;
	Event e = Event("fjcjg", "gccjc", "12.12.2020", "12:12", 15, "gyfi.fv");
	try
	{
		repo1.updateEvent(e, "gwhsb.swi", "dgwbh", "23.12.2020", "12:13", 78);
	}
	catch (RepoException re) {}
	repo1.addEvent(e);
	assert(repo1.updateEvent(e, "gwhsb.swi", "dgwbh", "23.12.2020", "12:13", 78) == true);
	Event e2 = repo1.findByTitle("fjcjg");
	assert(e2.getLink() == "gwhsb.swi");
}

void Tests::testAddService()
{
	Repository repo1;
	Repository repo2;
	EventValidator ev;
	OperationManager op;
	Service service(repo1, repo2, ev, op);
	try {
		service.addEvent("gfifi", "yffifi", "31.56.2020", "15:15", 45, "yf.igi");}
	catch (ValidatorException ve) {}
	assert(service.addEvent("gfifi", "yffifi", "31.10.2020", "15:15", 45, "yf.igi") == 0);
	try {
		service.addEvent("gfifi", "yffifi", "31.10.2020", "15:15", 45, "yf.igi");}
	catch (RepoException re) {}
    std::vector<Event>events = service.eventList();
	assert(events.size() == 1);
	assert(events[0].getTitle() == "gfifi");
}

void Tests::testRemoveService()
{
	Repository repo1;
	Repository repo2;
	EventValidator ev;
	OperationManager op;
	Service service(repo1, repo2, ev, op);
	try {
		service.removeEvent("gfifi");}
	catch (RepoException re) {}
	assert(service.addEvent("gfifi", "yffifi", "31.10.2020", "15:15", 45, "yf.igi") == 0);
	assert(service.removeEvent("gfifi") == 0);
	std::vector<Event>events = service.eventList();
	assert(events.size() == 0);
}

void Tests::testUpdateService()
{
	Repository repo1;
	Repository repo2;
	EventValidator ev;
	OperationManager op;
	Service service(repo1, repo2, ev, op);
	try {
		service.updateEvent("gfifi", "tugcu", "12.12.2012", "12:12", 5, "iyfg.gi");}
	catch (RepoException re) {}
	try {
		service.updateEvent("gfifi", "tugcu", "12.12.2012", "56:12", 5, "iyfg.gi");}
	catch (ValidatorException ve) {}
	assert(service.addEvent("gfifi", "yffifi", "31.10.2020", "15:15", 45, "yf.igi") == 0);
	assert(service.updateEvent("gfifi", "tugcu", "12.12.2012", "12:12", 5, "iyfg.gi") == 0);
	std::vector<Event>events = service.eventList();
	assert(events[0].getLink() == "iyfg.gi");
}

void Tests::testNextUserService()
{
	Repository repo1;
    Event e1 = Event("fj", "gccjc", "12.12.2020", "12:12", 15, "gyfi.fv");
	Event e2 = Event("cjg", "gccjc", "11.08.2020", "12:12", 15, "gyfi.fv");
	Event e3 = Event("jg", "gccjc", "12.12.2020", "10:12", 15, "gyfi.fv");
	repo1.addEvent(e1);
	repo1.addEvent(e2);
	repo1.addEvent(e3);
	Repository repo2;
	EventValidator ev;
	OperationManager op;
	Service service(repo1, repo2, ev, op);
	std::vector<Event> user_list = service.nextEventUserDA(0);
	assert(user_list[0].getTitle() == "cjg");
	assert(user_list[1].getTitle() == "jg");
	assert(user_list[2].getTitle() == "fj");
	std::vector<Event> user_list_m = service.nextEventUserDA(12);
	assert(user_list_m.size() == 2);
	assert(user_list_m[0].getTitle() == "jg");
	assert(user_list_m[1].getTitle() == "fj");

}

void Tests::testAddUserService()
{
	Repository repo1;
	Event e1 = Event("fj", "gccjc", "12.12.2020", "12:12", 15, "gyfi.fv");
	Event e2 = Event("cjg", "gccjc", "11.08.2020", "12:12", 40, "gyfi.fv");
	Event e3 = Event("jg", "gccjc", "12.12.2020", "10:12", 26, "gyfi.fv");
	repo1.addEvent(e1);
	repo1.addEvent(e2);
	repo1.addEvent(e3);
	Repository repo2;
	EventValidator ev;
	OperationManager op;
	Service service(repo1, repo2, ev, op);
	service.addEventUser(e1);
	service.addEventUser(e2);
	assert(repo2.len() == 2);
	assert(repo2.findByTitle("fj").getParticipants() == 16);
	assert(repo1.findByTitle("fj").getParticipants() == 16);
	assert(repo2.findByTitle("cjg").getParticipants() == 41);
	assert(repo1.findByTitle("cjg").getParticipants() == 41);
	service.removeEvent("fj");
	assert(repo2.len() == 1);
	std::vector <Event> user_list = service.userEventList();
	assert(user_list[0].getTitle() == "cjg");
	try {
		service.addEventUser(e2);
	}catch(RepoException re){}
}

void Tests::testRemoveUserService()
{
	Repository repo1;
	Event e1 = Event("fj", "gccjc", "12.12.2020", "12:12", 15, "gyfi.fv");
	Event e2 = Event("cjg", "gccjc", "11.08.2020", "12:12", 40, "gyfi.fv");
	Event e3 = Event("jg", "gccjc", "12.12.2020", "10:12", 26, "gyfi.fv");
	repo1.addEvent(e1);
	repo1.addEvent(e2);
	repo1.addEvent(e3);
	Repository repo2;
	EventValidator ev;
	OperationManager op;
	Service service(repo1, repo2, ev, op);
	service.addEventUser(e1);
	service.addEventUser(e2);
	assert(repo2.findByTitle("fj").getParticipants() == 16);
	assert(repo1.findByTitle("fj").getParticipants() == 16);
	assert(repo2.findByTitle("cjg").getParticipants() == 41);
	assert(repo1.findByTitle("cjg").getParticipants() == 41);
	service.removeEventUser("fj");
	assert(repo1.findByTitle("fj").getParticipants() == 15);
	assert(repo2.len() == 1);
	try {
		service.removeEventUser("jg");}
	catch (RepoException re)
	{ }
	
}

void Tests::testAll()
{
	this->testDomainGetters();
	this->testDomainSetters();
	this->testValidator();
	this->testAddRepo();
	this->testRemoveRepo();
	this->testUpdateRepo();
	this->testAddService();
	this->testRemoveService();
	this->testUpdateService();
	this->testNextUserService();
	this->testAddUserService();
	this->testRemoveUserService();
}