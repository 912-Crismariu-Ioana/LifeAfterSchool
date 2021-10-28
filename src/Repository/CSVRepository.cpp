#include "CSVRepository.h"
#include <iostream>
#include<fstream>
#include<algorithm>

void CSVRepository::save()
{
	FileRepository::save();
	std::ofstream f(this->cvsfile);
	if (!f.is_open())
		return;
	{
		std::for_each(this->events.begin(), this->events.end(), [&f](const auto& x) {f << x << "\n"; });
	}
	f.close();
}