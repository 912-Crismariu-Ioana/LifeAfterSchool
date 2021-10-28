#include "userGUITable.h"
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <Windows.h>
#include <shellapi.h>
#include <QLayout>
#include <QHeaderView>




userGUITable::userGUITable(Service& service, const std::string& filename, QWidget* parent) : QWidget{ parent }, filename{ filename }, service{ service }
{

	this->initGUI();
	this->connectSignalsAndSlots();

}

userGUITable::~userGUITable()
{

}

void userGUITable::initGUI()
{

	QHBoxLayout* layout = new QHBoxLayout{ this };
	QWidget* buttonsWidget = new QWidget{};
	QFont f{ "Corbel Light", 16 };
	QHBoxLayout* hLayout = new QHBoxLayout{ buttonsWidget };
	this->personalEvents = new QPushButton("See personal list of events");
	this->personalEvents->setFont(f);
	this->availableEvents = new QPushButton("See available events");
	this->availableEvents->setFont(f);
	hLayout->addWidget(this->personalEvents);
	hLayout->addWidget(this->availableEvents);
	layout->addWidget(buttonsWidget);
	this->admintableModel = new EventsTableModel{ this->service, "admin" };
	this->usertableModel = new EventsTableModel{ this->service, "user" };
}

void userGUITable::connectSignalsAndSlots()
{
	QObject::connect(this->personalEvents, &QPushButton::clicked, this, &userGUITable::initTableViewPersonal);
	QObject::connect(this->availableEvents, &QPushButton::clicked, this, &userGUITable::initTableViewAvailable);
}

void userGUITable::connectSignalsAndSlotsPersonal()
{
	QObject::connect(this->deleteEventButton, &QPushButton::clicked, this, &userGUITable::deleteEventButtonHandler);
	QObject::connect(this->open, &QPushButton::clicked, this, &userGUITable::openFile);
}

void userGUITable::addEventButtonHandler()
{
	try
	{
		std::vector<Event> all = this->service.eventList();
		int rowidx = this->admintableView->selectionModel()->currentIndex().row();
		std::string name = this->admintableModel->index(rowidx, 0).data().toString().toStdString();
		std::string  description = this->admintableModel->index(rowidx, 1).data().toString().toStdString();
		std::string date = this->admintableModel->index(rowidx, 2).data().toString().toStdString();
		std::string time = this->admintableModel->index(rowidx, 3).data().toString().toStdString();
		int participants = this->admintableModel->index(rowidx, 4).data().toString().toInt();
		std::string link = this->admintableModel->index(rowidx, 5).data().toString().toStdString();
		Event e{ name, description, date, time, participants, link };
		this->service.addEventUser(e);
		this->admintableView->reset();
		this->usertableModel->insertRow(this->service.userEventsSize());
	}
	catch (std::exception& e)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", e.what());
	}
}

void userGUITable::connectSignalsAndSlotsAvailable()
{
	QObject::connect(this->addEventButton, &QPushButton::clicked, this, &userGUITable::addEventButtonHandler);
	QObject::connect(this->goToPage, &QPushButton::clicked, this, &userGUITable::openURL);
}


void userGUITable::initTableViewAvailable()
{
	this->admin = new QWidget;
	this->admin->setMinimumHeight(1000);
	this->admin->setMinimumWidth(1000);
	this->admintableView = new QTableView{};
	this->admintableView->setModel(this->admintableModel);
	this->admintableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->admintableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	QVBoxLayout* layout = new QVBoxLayout{ this->admin };
	layout->addWidget(this->admintableView);
	QFont f{ "Corbel Light", 16 };
	this->addEventButton = new QPushButton("Add Event");
	this->addEventButton->setFont(f);
	this->goToPage = new QPushButton("Go To Page");
	this->goToPage->setFont(f);
	QWidget* buttonsWidget = new QWidget{};
	QHBoxLayout* hLayout = new QHBoxLayout{ buttonsWidget };
	hLayout->addWidget(this->addEventButton);
	hLayout->addWidget(this->goToPage);
	layout->addWidget(buttonsWidget);
	this->connectSignalsAndSlotsAvailable();
	this->admin->show();
}




void userGUITable::deleteEventButtonHandler()
{

	std::vector<Event> all = this->service.eventList();
	int rowidx = this->usertableView->selectionModel()->currentIndex().row();
	std::string name = this->usertableModel->index(rowidx, 0).data().toString().toStdString();
	this->service.removeEventUser(name);
	this->usertableModel->removeRow(rowidx-1);
}


void userGUITable::initTableViewPersonal()
{
	this->user = new QWidget;
	this->usertableView = new QTableView{};
	this->user->setMinimumHeight(1000);
	this->user->setMinimumWidth(1000);
	this->usertableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->usertableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	this->usertableView->setModel(this->usertableModel);
	QVBoxLayout* layout = new QVBoxLayout{ this->user };
	layout->addWidget(this->usertableView);
	QFont f{ "Corbel Light", 16 };
	this->deleteEventButton = new QPushButton("Delete Event");
	this->deleteEventButton->setFont(f);
	this->open = new QPushButton("Open File");
	this->open->setFont(f);
	QWidget* buttonsWidget = new QWidget{};
	QHBoxLayout* hLayout = new QHBoxLayout{ buttonsWidget };
	hLayout->addWidget(this->deleteEventButton);
	hLayout->addWidget(this->open);
	layout->addWidget(buttonsWidget);
	this->connectSignalsAndSlotsPersonal();
	this->user->show();
}


void userGUITable::openURL()
{
	int rowidx = this->admintableView->selectionModel()->currentIndex().row();
	QDesktopServices::openUrl(QUrl{this->admintableModel->index(rowidx, 5).data().toString()});
}

void userGUITable::openFile()
{
	ShellExecuteA(NULL, "open", this->filename.c_str(), NULL, NULL, SW_SHOWNORMAL);
}