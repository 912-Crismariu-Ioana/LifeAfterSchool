#include "EventValidator.h"
#include<stdexcept>

int EventValidator::validate(Event e)
{
	if (e.getTitle().length() == 0 || e.getDescription().length() == 0 || e.getDate().length() == 0 || e.getTime().length() == 0 || e.getParticipants() == 0 || e.getLink().length() == 0)
	{
		ValidatorException ve("Invalid input! You provided empty fields!");
		throw ve;
	}
	if (e.getDate().find_first_of(".") == e.getDate().npos || e.getDate().find_last_of(".") == e.getDate().npos)
	{
			ValidatorException ve("Invalid date!");
			throw ve;
	}
	if (e.getTime().find_first_of(":") == e.getTime().npos)
	{
		ValidatorException ve("Invalid time!");
		throw ve;
	}
	try 
	{
		e.getDay();}
	catch (const std::invalid_argument& ia) {
		ValidatorException ve("Invalid day!");
		throw ve;
	}
	try 
	{
		e.getMonth();}
	catch (const std::invalid_argument& ia){
		ValidatorException ve("Invalid month!");
		throw ve;
	}
	try
	{
		e.getYear();}
	catch (const std::invalid_argument& ia)
	{
		ValidatorException ve("Invalid year!");
		throw ve;
	}
	try
	{
		e.getHour();}
	catch (const std::invalid_argument& ia)
	{
		ValidatorException ve("Invalid hour!");
		throw ve;
	}
	try
	{
		e.getMinute();}
	catch (const std::invalid_argument& ia)
	{
		ValidatorException ve("Invalid minute!");
		throw ve;
	}
	if (e.getLink().find_first_of(".") == e.getLink().npos)
	{
		ValidatorException ve("Provide a valid link!");
		throw ve;
	}
	if (e.getDay() > 31 || e.getMonth() > 12)
	{
		ValidatorException ve("Provide a valid date!");
		throw ve;
	}
	if (e.getHour() > 23 || e.getMinute() > 59)
	{
		ValidatorException ve("Provide a valid time!");
		throw ve;
	}
	return 0;
}