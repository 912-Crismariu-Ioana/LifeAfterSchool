#pragma once
#include "FileRepository.h"
class AbstractExternalRepository : public FileRepository
{
protected :
	std::string displayfile;
	virtual void save() = 0;
public:
	AbstractExternalRepository(const std::string& textfile, const std::string& displayfile) :displayfile{ filename }, FileRepository(textfile){this->load();}
};
