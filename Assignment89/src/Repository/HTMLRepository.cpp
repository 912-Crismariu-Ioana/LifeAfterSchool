#include "HTMLRepository.h"
#include <iostream>
#include<fstream>
#include<algorithm>

void HTMLRepository::save()
{
	FileRepository::save();
	std::ofstream f(this->htmlfile);
	if (!f.is_open())
		return;
	f << "<!DOCTYPE html> ";
	f << "<html>";
	f << "<head>";
	f << "<title>Life After School</title> ";
	f << "</head>";
	f << "<body>";
	f << "<table border=\"1\">";
	f << "<tr>";
	f << "<td>Title</td>";
	f << "<td>Description</td>";
	f << "<td>Date</td>";
	f << "<td>Time</td>";
	f << "<td>Participants</td>";
	f << "<td>Link</td>";
	f << "</tr>";
	for (Event& e : this->events)
	{
		f << "<tr>";
		f << "<td>" << e.getTitle() << "</td>";
		f << "<td>" << e.getDescription() << "</td>";
		f << "<td>" << e.getDate() << "</td>";
		f << "<td>" << e.getTime() << "</td>";
		f << "<td>" << std::to_string(e.getParticipants()) << "</td>";
		f << "<td>" << e.getLink() << "</td>";
		f << "</tr>";
	}
	f << "</table>";
	f << "</body>";
	f << "</html>";
	f.close();
}