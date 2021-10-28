#pragma once
#include "AbstractExternalRepository.h"
class CSVRepository : public AbstractExternalRepository
{
protected:
	std::string cvsfile;
	void save() override;
public:
	CSVRepository(const std::string& textfile, const std::string& cvsfile) : cvsfile{ cvsfile }, AbstractExternalRepository(textfile, cvsfile){}

};