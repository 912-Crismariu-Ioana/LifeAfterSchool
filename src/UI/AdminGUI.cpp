#include "AdminGUI.h"
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>


adminGUI::adminGUI(Service& service, QWidget* parent): QWidget{parent}, service{service}
{
    this->initGUI();
	this->connectSignalsAndSlots();
	this->populateEventList();

}

adminGUI::~adminGUI()
{

}

void adminGUI::restart()
{
	this->service.restart();
}

void adminGUI::initGUI()
{
	QHBoxLayout* layout = new QHBoxLayout{ this };

	this->eventList = new QListWidget{};
	this->eventList->setSelectionMode(QAbstractItemView::SingleSelection);
	layout->addWidget(this->eventList);

	QWidget* rightSide = new QWidget{};
	QVBoxLayout* vLayout = new QVBoxLayout{ rightSide };

	QWidget* eventDataWidget = new QWidget{};
	QFormLayout* formLayout = new QFormLayout{ eventDataWidget };
	this->titleEdit = new QLineEdit{};
	this->descriptionEdit = new QTextEdit{};
	this->dateEdit = new QLineEdit{};
	this->timeEdit = new QLineEdit{};
	this->participantsEdit = new QLineEdit{};
	this->linkEdit = new QTextEdit{};
	QFont f{ "Corbel Light", 16 };
	QLabel* titleLabel = new QLabel{ "&Event Title:" };
	titleLabel->setBuddy(this->titleEdit);
	QLabel* descriptionLabel = new QLabel{ "&Event Description:" };
	descriptionLabel->setBuddy(this->descriptionEdit);
	QLabel* dateLabel = new QLabel{ "&Event Date:" };
	dateLabel->setBuddy(this->dateEdit);
	QLabel* timeLabel = new QLabel{ "&Event Time:" };
	timeLabel->setBuddy(this->timeEdit);
	QLabel* participantsLabel = new QLabel{ "&Event Participants:" };
	participantsLabel->setBuddy(this->participantsEdit);
	QLabel* linkLabel = new QLabel{ "&Event Link:" };
	linkLabel->setBuddy(this->linkEdit);
	titleLabel->setFont(f);
	descriptionLabel->setFont(f);
	dateLabel->setFont(f);
	timeLabel->setFont(f);
	participantsLabel->setFont(f);
	linkLabel->setFont(f);
	this->titleEdit->setFont(f);
	this->descriptionEdit->setFont(f);
	this->dateEdit->setFont(f);
	this->timeEdit->setFont(f);
	this->participantsEdit->setFont(f);
	this->linkEdit->setFont(f);
	formLayout->addRow(titleLabel, this->titleEdit);
	formLayout->addRow(descriptionLabel , this->descriptionEdit);
	formLayout->addRow(dateLabel, this->dateEdit);
	formLayout->addRow(timeLabel, this->timeEdit);
	formLayout->addRow(participantsLabel, this->participantsEdit);
	formLayout->addRow(linkLabel, this->linkEdit);
	vLayout->addWidget(eventDataWidget);

	QWidget* buttonsWidget = new QWidget{};
	QHBoxLayout* hLayout = new QHBoxLayout{ buttonsWidget };
	this->addEventButton = new QPushButton("Add Event");
	this->addEventButton->setFont(f);
	this->deleteEventButton = new QPushButton("Delete Event");
	this->deleteEventButton->setFont(f);
	this->updateEventButton = new QPushButton("Update Event");
	this->updateEventButton->setFont(f);
	this->goToPage = new QPushButton("Go To Page");
	this->goToPage->setFont(f);
	this->undo = new QPushButton("Undo");
	this->undo->setFont(f);
	this->redo = new QPushButton("Redo");
	this->redo->setFont(f);


	hLayout->addWidget(this->addEventButton);
	hLayout->addWidget(this->deleteEventButton);
	hLayout->addWidget(this->updateEventButton);
	hLayout->addWidget(this->goToPage);
	hLayout->addWidget(this->undo);
	hLayout->addWidget(this->redo);
	vLayout->addWidget(buttonsWidget);

	layout->addWidget(this->eventList);
	layout->addWidget(rightSide);
	this->u = new QShortcut(this);
	this->u->setKey(QKeySequence("Ctrl+Z"));
	this->r = new QShortcut(this);
	this->r->setKey(QKeySequence("Ctrl+Y"));
	this->service.restart();
}

void adminGUI::connectSignalsAndSlots()
{
	QObject::connect(this, &adminGUI::show, this, &adminGUI::restart);

	QObject::connect(this, &adminGUI::eventsUpdatedSignal, this, &adminGUI::populateEventList);
	
	QObject::connect(this->eventList, &QListWidget::itemSelectionChanged, this, [this]() {this->listItemChanged(); });

	QObject::connect(this->addEventButton, &QPushButton::clicked, this, &adminGUI::addEventButtonHandler);

	QObject::connect(this->deleteEventButton, &QPushButton::clicked, this, &adminGUI::deleteEventButtonHandler);

	QObject::connect(this->updateEventButton, &QPushButton::clicked, this, &adminGUI::updateEventButtonHandler);

	QObject::connect(this, SIGNAL(addEventSignal(const std::string&, const std::string&, const std::string& , const std::string&, const std::string&, const std::string&)), this, SLOT(addEvent(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&)), Qt::UniqueConnection);

	QObject::connect(this, SIGNAL(updateEventSignal(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&)), this, SLOT(updateEvent(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&)), Qt::UniqueConnection);

	QObject::connect(this->goToPage, &QPushButton::clicked, this, &adminGUI::openURL);

	QObject::connect(this->undo, &QPushButton::clicked, this, &adminGUI::undoAction);

	QObject::connect(this->redo, &QPushButton::clicked, this, &adminGUI::redoAction);

	QObject::connect(this->u, &QShortcut::activated, this, &adminGUI::undoAction);

	QObject::connect(this->r, &QShortcut::activated, this, &adminGUI::redoAction);
}

void adminGUI::addEvent(const std::string& title, const std::string& description, const std::string& date, const std::string& time, const std::string& participants, const std::string& link)
{
	try
	{
		int partips = stoi(participants);
		this->service.addEvent(title, description, date, time, partips, link);
		emit eventsUpdatedSignal();
	} 
	catch(std::exception& e)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", e.what());
	}
	
}

void adminGUI::addEventButtonHandler()
{
	QString title = this->titleEdit->text();
	QString description = this->descriptionEdit->toPlainText();
	QString date = this->dateEdit->text();
	QString time = this->timeEdit->text();
	QString participants = this->participantsEdit->text();
	QString link = this->linkEdit->toPlainText();

	emit addEventSignal(title.toStdString(), description.toStdString(), date.toStdString(), time.toStdString(), participants.toStdString(), link.toStdString());
}

void adminGUI::updateEvent(const std::string& title, const std::string& description, const std::string& date, const std::string& time, const std::string& participants, const std::string& link)
{
	try
	{
		int partips = stoi(participants);
		this->service.updateEvent(title, description, date, time, partips, link);
		emit eventsUpdatedSignal();
	}
	catch (std::exception& e)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", e.what());
	}

	
}

void adminGUI::updateEventButtonHandler()
{
	QString title = this->titleEdit->text();
	QString description = this->descriptionEdit->toPlainText();
	QString date = this->dateEdit->text();
	QString time = this->timeEdit->text();
	QString participants = this->participantsEdit->text();
	QString link = this->linkEdit->toPlainText();

	emit updateEventSignal(title.toStdString(), description.toStdString(), date.toStdString(), time.toStdString(), participants.toStdString(), link.toStdString());
}

void adminGUI::deleteEventButtonHandler()
{
	int idx = this->getSelectedIndex();

	if (idx < 0 || idx >= this->service.eventList().size())
		return;

	std::vector<Event> events = this->service.eventList();
	std::string title = events[idx].getTitle();

	this->service.removeEvent(title);

	emit eventsUpdatedSignal();
}

void adminGUI::populateEventList()
{
	if (this->eventList->count() > 0)
		this->eventList->clear();

	std::vector<Event> events = this->service.eventList();

	for (auto ev : events)
	{
		QString itemInList = QString::fromStdString(ev.getTitle());
		QFont f{ "Corbel Light", 16 };
		QListWidgetItem* item = new QListWidgetItem{ itemInList };
		item->setFont(f);
		this->eventList->addItem(item);
	}

	if (events.size() > 0)
		this->eventList->setCurrentRow(0);
}

int adminGUI::getSelectedIndex()
{
	if (this->eventList->count() == 0)
		return -1;

	QModelIndexList index = this->eventList->selectionModel()->selectedIndexes();
	if (index.size() == 0)
	{
		this->titleEdit->clear();
		this->descriptionEdit->clear();
		this->dateEdit->clear();
		this->timeEdit->clear();
		this->participantsEdit->clear();
		this->linkEdit->clear();
		return -1;
	}

	int idx = index.at(0).row();
	return idx;
}

void adminGUI::listItemChanged()
{
	int idx = this->getSelectedIndex();
	if (idx == -1)
		return;

	std::vector<Event> events = this->service.eventList();

	if (idx >= events.size())
		return;
	Event ev = events[idx];

	this->titleEdit->setText(QString::fromStdString(ev.getTitle()));
	this->descriptionEdit->setText(QString::fromStdString(ev.getDescription()));
	this->dateEdit->setText(QString::fromStdString(ev.getDate()));
	this->timeEdit->setText(QString::fromStdString(ev.getTime()));
	this->participantsEdit->setText(QString::fromStdString(std::to_string(ev.getParticipants())));
	this->linkEdit->setText(QString::fromStdString(ev.getLink()));


}

void adminGUI::openURL()
{
	QDesktopServices::openUrl(QUrl{ this->linkEdit->toPlainText() });
}


void adminGUI::undoAction()
{
	try
	{
		this->service.undo();
		emit eventsUpdatedSignal();
	}
	catch (std::exception& e)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", e.what());
	}
}

void adminGUI::redoAction()
{
	try
	{
		this->service.redo();
		emit eventsUpdatedSignal();
	}
	catch (std::exception& e)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", e.what());
	}
}
