#include "Operation.h"

void AddEvent::execute()
{
	this->repo.addEvent(this->e);
}

void AddEvent::undo()
{
	this->repo.removeEvent(this->e);
}

void AddEvent::redo()
{
	this->repo.addEvent(this->e);
}

void RemoveEvent::execute()
{
	this->repo.removeEvent(this->e);
}

void RemoveEvent::undo()
{
	this->repo.addEvent(this->e);
}

void RemoveEvent::redo()
{
	this->repo.removeEvent(this->e);
}

void UpdateEvent::execute()
{
	this->repo.updateEvent(this->e, this->link, this->description, this->date, this->time, this->participants);
}

void UpdateEvent::undo()
{
	std::string oldDesrc = e.getDescription();
	std::string oldDate = e.getDate();
	std::string oldTime = e.getTime();
	int oldParticipants = e.getParticipants();
	std::string oldLink = e.getLink();
	this->repo.updateEvent(this->e, oldLink, oldDesrc, oldDate, oldTime, oldParticipants);
}

void UpdateEvent::redo()
{
	this->repo.updateEvent(this->e, this->link, this->description, this->date, this->time, this->participants);
}

void CascadedOperation::execute()
{
	for (int i = 0; i < ops.size(); i++)
	{
		this->ops[i]->execute();
	}
}

void CascadedOperation::undo()
{
	for (int i = 0; i < ops.size(); i++)
	{
		this->ops[i]->undo();
	}
}

void CascadedOperation::redo()
{
	for (int i = 0; i < ops.size(); i++)
	{
		this->ops[i]->redo();
	}
}
