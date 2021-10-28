#pragma once
#include "AbstractExternalRepository.h"

class HTMLRepository : public AbstractExternalRepository
{
protected:
	std::string htmlfile;
	void save();
public:
	HTMLRepository(std::string txtfile, std::string htmlfile) :htmlfile{ htmlfile }, AbstractExternalRepository(txtfile, htmlfile) { }

};
