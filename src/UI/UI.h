#pragma once
#include "Service.h"
class UI {
private:
	Service& service;

public:
	UI(Service& serv):service{serv}{}
	void start();
	void menuAdmin();
	void menuUser();
	void addEventUI();
	void removeEventUI();
	void updateEventUI();
	void removeUserEventUI();
	void nextUserEventUIDA();
};
