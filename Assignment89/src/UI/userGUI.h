#pragma once
#include <qwidget.h>
#include "Service.h"
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QShortcut>

using namespace QtCharts;

class userGUI : public QWidget
{
	Q_OBJECT

public:
	userGUI(Service& service, const std::string& filename, QWidget* parent = 0);
	~userGUI();
private:
	std::string filename;
	Service& service;
	QWidget* user;
	QWidget* admin;
	QMainWindow* popularEvents;
	QListWidget* userEventList;
	QListWidget* adminEventList;
	QLineEdit* userTitleEdit;
	QTextEdit* userDescriptionEdit;
	QLineEdit* userDateEdit;
	QLineEdit* userTimeEdit;
	QLineEdit* userParticipantsEdit;
	QTextEdit* userLinkEdit;
	QPushButton* personalEvents;
	QPushButton* availableEvents;
	QPushButton* seePopularEvents;
	QPushButton* addEventButton;
	QPushButton* deleteEventButton;
	QPushButton* goToPage;
	QPushButton* open;
	QPushButton* undo;
	QPushButton* redo;
	QShortcut* u;
	QShortcut* r;


public:
	void initGUI();
	void initPersonal();
	void initAvailable();
	void seePopularEventsChart();
	int getSelectedIndexUser();
	int getSelectedIndexAdmin();
	void connectSignalsAndSlots();
	void connectSignalsAndSlotsPersonal();
	void connectSignalsAndSlotsAvailable();

	void populateUserEventList();
	void populateAdminEventList();
	void listItemChangedUser();
	void listItemChangedAdmin();

	void addEventButtonHandler();
	void deleteEventButtonHandler();
	void openURL();
	void openFile();
	void undoAction();
	void redoAction();
signals:
	void eventsUpdatedSignal();
	void addEventSignal(const std::string& title, const std::string& description, const std::string& date, const std::string& time, const std::string& participants, const std::string& link);


public slots:
	void addEvent(const std::string& title, const std::string& description, const std::string& date, const std::string& time, const std::string& participants, const std::string& link);


};
