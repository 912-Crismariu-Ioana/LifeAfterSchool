#pragma once
#include <qwidget.h>
#include "Service.h"
#include <QPushButton>
#include <QLabel>
#include <QMainWindow>
#include <QTableView>
#include "CustomTableModel.h"

class userGUITable : public QWidget
{
	Q_OBJECT

public:
	userGUITable(Service& service, const std::string& filename, QWidget* parent = 0);
	~userGUITable();
private:
	std::string filename;
	Service& service;
	QWidget* user;
	QWidget* admin;
	QPushButton* personalEvents;
	QPushButton* availableEvents;
	QPushButton* seePopularEvents;
	QPushButton* addEventButton;
	QPushButton* deleteEventButton;
	QPushButton* goToPage;
	QPushButton* open;
	EventsTableModel* admintableModel;
	EventsTableModel* usertableModel;
	QTableView* admintableView;
	QTableView* usertableView;

public:
	void initGUI();
	void initTableViewPersonal();
	void initTableViewAvailable();
	void connectSignalsAndSlots();
	void connectSignalsAndSlotsPersonal();
	void connectSignalsAndSlotsAvailable();


	void addEventButtonHandler();
	void deleteEventButtonHandler();
	

	void openURL();
	void openFile();


};