#include"Repository.h"
#include<time.h> 
#include <exception>

Repository::Repository() {

}


 Event& Repository::findByTitle(const std::string& title)
{
	for (Event& e : this->events)
	{
		if (e.getTitle() == title)
		{
			return e;
		}
	}
	RepoException re{ "No event with the given name exists in the database!" };
	throw re;
}



bool Repository::addEvent(Event& e) {
	for (Event& currev : this->events)
	{
		if (currev == e)
		{
			RepoException re{ "Event you wanted to add already exists in the database!" };
			throw re;
		}
	}
	this->events.push_back(e);
	return true;
}

bool Repository::removeEvent(Event& e)
{
	auto it = std::find(this->events.begin(), this->events.end(), e);
	if (it != this->events.end())
	{
		this->events.erase(it);
		return true;
	}
	RepoException re{ "Event you wanted to remove does not exist in the database!" };
	throw re;
}

bool Repository::updateEvent(Event& e, const std::string& link, const std::string& description,const std::string& date, const std::string& time, int participants)
{
	auto it = std::find(this->events.begin(), this->events.end(), e);
	if (it != this->events.end())
	{
		(*it).setLink(link);
		(*it).setDescription(description);
		(*it).setDate(date);
		(*it).setTime(time);
		(*it).setParticipants(participants);
		return true;
	}
	RepoException re{ "Event you wanted to update does not exist in the database!" };
	throw re;
}


std::vector<Event> Repository::getAll()
{	events = this->events;
	return events;}

int Repository::len()
{
	return this->events.size();
}

void populateRepository(Repository& repo)
{
	Event e1{ "Van Gogh: The Immersive Experience",
		"Van Gogh: The Immersive Experience is a 20,000 square foot light and sound spectacular featuring two-story projections of the artist's most compelling works. Encounter the brilliance of one of history's greatest artists in a 360-degree exhibit of unparalleled proportions.",
		"26.06.2021",
		"16:00",
		10,
		"https://vangoghexpo.com/new-york/?utm_source=facebook&utm_medium=event&utm_campaign=96017_nyc&fbclid=IwAR0846-ghAsK4H7mAT1c32yv1gsf1uNI6an79LMu13y7VqkTgPSmHSWXaSY" };
	repo.addEvent(e1);
	Event e2{ "UNTOLD Festival 2021",
		"Together we will write a new chapter of the UNTOLD story!",
		"05.08.2021",
		"14:00",
		12,
		"https://www.untold.com/"

	};
	repo.addEvent(e2);
	Event e3{ "Jazz in the Park",
		"8th edition of the open-air music festival.",
		"24.06.2021",
		"14:00",
		23,
		"https://www.jazzinthepark.ro/"
	};
	repo.addEvent(e3);
	Event e4{"SPORTS FESTIVAL",
		"the heartbeats festival",
		"22.07.2021",
		"13:00",
		17,
		"https://www.sportsfestival.com/"
	};
	repo.addEvent(e4);
	Event e5{
		"TIFF",
		"Transilvania International Film Festival",
		"23.07.2021",
		"14:00",
		23,
		"https://tiff.ro/?fbclid=IwAR2tuJnh04El6OOF7muNzKjd1c7sOInMDWrB_JoK6IF4u9qM15fq48OI0Yo",
	};
	repo.addEvent(e5);
	Event e6{
		"Space in the City",
		"Come live the greatest space adventure of your life!",
		"16.05.2021",
		"12:00",
		5,
		"https://www.nasaexpo.ro/"
	};
	repo.addEvent(e6);
	Event e7{
		"Career Fair",
		"Top Companies are hiring RIGHT NOW!",
		"26.03.2021",
		"10:00",
		23,
		"https://www.targuldecariere.ro/"
	};
	repo.addEvent(e7);
	Event e8{
		"TEDxCluj 2021",
		"Over 25 speakers and performers",
		"12.06.2021",
		"11:00",
		15,
		"https://tedxcluj.com/"
	};
	repo.addEvent(e8);
	Event e9{
		"Classy Film Festival",
		"Cult & Classic Film Festival",
		"20.05.2021",
		"19:00",
		10,
		"https://classyfilmfestival.ro/"
	};
	repo.addEvent(e9);
	Event e10{
		"Electric Castle",
		"Electric Castle is a one-of-a-kind music festival happening at Banffy Castle in Transylvania.",
		"14.07.2021",
		"12:00",
		28,
		"https://electriccastle.ro/"
	};
	repo.addEvent(e10);
}