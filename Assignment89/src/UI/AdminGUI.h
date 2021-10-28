#pragma once
#include <qwidget.h>
#include "Service.h"
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QShortcut>

class adminGUI : public QWidget
{
	Q_OBJECT

public:
	adminGUI(Service& service, QWidget* parent = 0);
	~adminGUI();
private:
	Service& service;
	QListWidget* eventList;
	QLineEdit* titleEdit;
	QTextEdit* descriptionEdit;
	QLineEdit* dateEdit;
	QLineEdit* timeEdit;
	QLineEdit* participantsEdit;
	QTextEdit* linkEdit;
	QPushButton* addEventButton;
	QPushButton* deleteEventButton;
	QPushButton* updateEventButton;
	QPushButton* goToPage;
	QPushButton* tableView;
	QPushButton* undo;
	QPushButton* redo;
	QShortcut* u;
	QShortcut* r;
	void restart();

public:
	void initGUI();
	int getSelectedIndex();
	void connectSignalsAndSlots();

	void populateEventList();
	void listItemChanged();

	void addEventButtonHandler();
	void deleteEventButtonHandler();
	void updateEventButtonHandler();

	void openURL();
	void undoAction();
	void redoAction();
signals:
	void eventsUpdatedSignal();
	void addEventSignal(const std::string& title, const std::string& description, const std::string& date, const std::string& time, const std::string& participants, const std::string& link);
	void updateEventSignal(const std::string& title, const std::string& description, const std::string& date, const std::string& time, const std::string& participants, const std::string& link);
	

public slots:
	void addEvent(const std::string& title, const std::string& description, const std::string& date, const std::string& time, const std::string& participants, const std::string& link);
	void updateEvent(const std::string& title, const std::string& description, const std::string& date, const std::string& time, const std::string& participants, const std::string& link);
	
};
