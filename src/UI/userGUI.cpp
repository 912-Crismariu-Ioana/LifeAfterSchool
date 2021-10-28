#include "userGUI.h"
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include<Windows.h>
#include<shellapi.h>



userGUI::userGUI(Service& service, const std::string& filename, QWidget* parent) : QWidget{ parent }, filename{ filename }, service{ service }
{

	this->initGUI();
	this->connectSignalsAndSlots();
	
}

userGUI::~userGUI()
{

}

void userGUI::initGUI()
{
	
	QHBoxLayout* layout = new QHBoxLayout{ this};
	QWidget* buttonsWidget = new QWidget{};
	QFont f{ "Corbel Light", 16 };
	QHBoxLayout* hLayout = new QHBoxLayout{ buttonsWidget };
	this->personalEvents = new QPushButton("See personal list of events");
	this->personalEvents->setFont(f);
	this->availableEvents = new QPushButton("See available events");
	this->availableEvents->setFont(f);
	this->seePopularEvents = new QPushButton("See popular events");
	this->seePopularEvents->setFont(f);
	hLayout->addWidget(this->personalEvents);
	hLayout->addWidget(this->availableEvents);
	hLayout->addWidget(this->seePopularEvents);
	layout->addWidget(buttonsWidget);
}

void userGUI::connectSignalsAndSlots()
{
	QObject::connect(this->personalEvents, &QPushButton::clicked, this, &userGUI::initPersonal);
	QObject::connect(this->availableEvents, &QPushButton::clicked, this, &userGUI::initAvailable);
	QObject::connect(this->seePopularEvents, & QPushButton::clicked, this, & userGUI::seePopularEventsChart);
}


void userGUI::initAvailable()
{
	this->admin = new QWidget;
	QHBoxLayout* layout = new QHBoxLayout{ this->admin };
	this->adminEventList = new QListWidget{};
	this->adminEventList->setSelectionMode(QAbstractItemView::SingleSelection);
	layout->addWidget(this->adminEventList);
	QWidget* rightSide = new QWidget{};
	QVBoxLayout* vLayout = new QVBoxLayout{ rightSide };
	QWidget* eventDataWidget = new QWidget{};
	QFormLayout* formLayout = new QFormLayout{ eventDataWidget };
	this->userTitleEdit = new QLineEdit{};
	this->userTitleEdit->setReadOnly(true);
	this->userDescriptionEdit = new QTextEdit{};
	this->userDescriptionEdit->setReadOnly(true);
	this->userDateEdit = new QLineEdit{};
	this->userDateEdit->setReadOnly(true);
	this->userTimeEdit = new QLineEdit{};
	this->userTimeEdit->setReadOnly(true);
	this->userParticipantsEdit = new QLineEdit{};
	this->userParticipantsEdit->setReadOnly(true);
	this->userLinkEdit = new QTextEdit{};
	this->userLinkEdit->setReadOnly(true);
	QFont f{ "Corbel Light", 16 };
	QLabel* titleLabel = new QLabel{ "&Event Title:" };
	titleLabel->setBuddy(this->userTitleEdit);
	QLabel* descriptionLabel = new QLabel{ "&Event Description:" };
	descriptionLabel->setBuddy(this->userDescriptionEdit);
	QLabel* dateLabel = new QLabel{ "&Event Date:" };
	dateLabel->setBuddy(this->userDateEdit);
	QLabel* timeLabel = new QLabel{ "&Event Time:" };
	timeLabel->setBuddy(this->userTimeEdit);
	QLabel* participantsLabel = new QLabel{ "&Event Participants:" };
	participantsLabel->setBuddy(this->userParticipantsEdit);
	QLabel* linkLabel = new QLabel{ "&Event Link:" };
	linkLabel->setBuddy(this->userLinkEdit);
	titleLabel->setFont(f);
	descriptionLabel->setFont(f);
	dateLabel->setFont(f);
	timeLabel->setFont(f);
	participantsLabel->setFont(f);
	linkLabel->setFont(f);
	this->userTitleEdit->setFont(f);
	this->userDescriptionEdit->setFont(f);
	this->userDateEdit->setFont(f);
	this->userTimeEdit->setFont(f);
	this->userParticipantsEdit->setFont(f);
	this->userLinkEdit->setFont(f);
	formLayout->addRow(titleLabel, this->userTitleEdit);
	formLayout->addRow(descriptionLabel, this->userDescriptionEdit);
	formLayout->addRow(dateLabel, this->userDateEdit);
	formLayout->addRow(timeLabel, this->userTimeEdit);
	formLayout->addRow(participantsLabel, this->userParticipantsEdit);
	formLayout->addRow(linkLabel, this->userLinkEdit);
	vLayout->addWidget(eventDataWidget);

	QWidget* buttonsWidget = new QWidget{};
	QHBoxLayout* hLayout = new QHBoxLayout{ buttonsWidget };
	this->addEventButton = new QPushButton("Add Event");
	this->addEventButton->setFont(f);
	this->goToPage = new QPushButton("Go To Page");
	this->goToPage->setFont(f);
	this->undo = new QPushButton("Undo");
	this->undo->setFont(f);
	this->redo = new QPushButton("Redo");
	this->redo->setFont(f);

	hLayout->addWidget(this->addEventButton);
	hLayout->addWidget(this->goToPage);
	hLayout->addWidget(this->undo);
	hLayout->addWidget(this->redo);
	vLayout->addWidget(buttonsWidget);

	layout->addWidget(this->adminEventList);
	layout->addWidget(rightSide);
	this->u = new QShortcut(this->admin);
	this->u->setKey(QKeySequence("Ctrl+Z"));
	this->r = new QShortcut(this->admin);
	this->r->setKey(QKeySequence("Ctrl+Y"));
	this->connectSignalsAndSlotsAvailable();
	this->populateAdminEventList();
	this->service.restart();
	this->admin->show();
}


void userGUI::seePopularEventsChart()
{
	this->popularEvents = new QMainWindow();
	QBarSeries* series = new QBarSeries();
	std::vector<Event> events = this->service.eventList();
	QFont f{ "Corbel Light", 11 };
	for (auto ev : events)
	{
		QBarSet* set0 = new QBarSet(QString::fromStdString(ev.getTitle()));
		(*set0).setLabelFont(f);
		*set0 << ev.getParticipants();
		series->append(set0);
	}
	QChart* chart = new QChart();
	chart->addSeries(series);
	chart->setTitle("Most popular events by number of participants");
	QFont f1{ "Corbel Light", 16 };
	chart->setFont(f1);
	chart->setAnimationOptions(QChart::SeriesAnimations);
	QStringList categories;
	categories << "Events";
	QBarCategoryAxis* axisX = new QBarCategoryAxis();
	axisX->append(categories);
	chart->addAxis(axisX, Qt::AlignBottom);
	series->attachAxis(axisX);

	QValueAxis* axisY = new QValueAxis();
	axisY->setRange(0, 100);
	chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisY);

	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignBottom);

	QChartView* chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	this->popularEvents->setCentralWidget(chartView);
	this->popularEvents->resize(2000, 900);
	this->popularEvents->show();



}

void userGUI::connectSignalsAndSlotsAvailable()
{
	QObject::connect(this->adminEventList, &QListWidget::itemSelectionChanged, this, [this]() {this->listItemChangedAdmin(); });
	QObject::connect(this, &userGUI::eventsUpdatedSignal, this, &userGUI::populateAdminEventList);
	QObject::connect(this->addEventButton, &QPushButton::clicked, this, &userGUI::addEventButtonHandler);
	QObject::connect(this, SIGNAL(addEventSignal(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&)), this, SLOT(addEvent(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&)), Qt::UniqueConnection);
	QObject::connect(this->goToPage, &QPushButton::clicked, this, &userGUI::openURL);
	QObject::connect(this->undo, &QPushButton::clicked, this, &userGUI::undoAction);
	QObject::connect(this->redo, &QPushButton::clicked, this, &userGUI::redoAction);
	QObject::connect(this->u, &QShortcut::activated, this, &userGUI::undoAction);
	QObject::connect(this->r, &QShortcut::activated, this, &userGUI::redoAction);
}

void userGUI::populateAdminEventList()
{
	if (this->adminEventList->count() > 0)
		this->adminEventList->clear();

	std::vector<Event> events = this->service.eventList();

	for (auto ev : events)
	{
		QString itemInList = QString::fromStdString(ev.getTitle());
		QFont f{ "Corbel Light", 16 };
		QListWidgetItem* item = new QListWidgetItem{ itemInList };
		item->setFont(f);
		this->adminEventList->addItem(item);
	}

	if (events.size() > 0)
		this->adminEventList->setCurrentRow(0);
}

void userGUI::addEvent(const std::string& title, const std::string& description, const std::string& date, const std::string& time, const std::string& participants, const std::string& link)
{
	try
	{
		int partips = stoi(participants);
		this->service.addEventUser(Event(title, description, date, time, partips, link));
		emit eventsUpdatedSignal();
	}
	catch (std::exception& e)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", e.what());
	}

}

void userGUI::addEventButtonHandler()
{
	QString title = this->userTitleEdit->text();
	QString description = this->userDescriptionEdit->toPlainText();
	QString date = this->userDateEdit->text();
	QString time = this->userTimeEdit->text();
	QString participants = this->userParticipantsEdit->text();
	QString link = this->userLinkEdit->toPlainText();

	emit addEventSignal(title.toStdString(), description.toStdString(), date.toStdString(), time.toStdString(), participants.toStdString(), link.toStdString());
}



int userGUI::getSelectedIndexAdmin()
{
	if (this->adminEventList->count() == 0)
		return -1;

	QModelIndexList index = this->adminEventList->selectionModel()->selectedIndexes();
	if (index.size() == 0)
	{
		this->userTitleEdit->clear();
		this->userDescriptionEdit->clear();
		this->userDateEdit->clear();
		this->userTimeEdit->clear();
		this->userParticipantsEdit->clear();
		this->userLinkEdit->clear();
		return -1;
	}

	int idx = index.at(0).row();
	return idx;
}

void userGUI::listItemChangedAdmin()
{
	int idx = this->getSelectedIndexAdmin();
	if (idx == -1)
		return;

	std::vector<Event> events = this->service.eventList();

	if (idx >= events.size())
		return;
	Event ev = events[idx];

	this->userTitleEdit->setText(QString::fromStdString(ev.getTitle()));
	this->userDescriptionEdit->setText(QString::fromStdString(ev.getDescription()));
	this->userDateEdit->setText(QString::fromStdString(ev.getDate()));
	this->userTimeEdit->setText(QString::fromStdString(ev.getTime()));
	this->userParticipantsEdit->setText(QString::fromStdString(std::to_string(ev.getParticipants())));
	this->userLinkEdit->setText(QString::fromStdString(ev.getLink()));


}


void userGUI::initPersonal()
{
	this->user = new QWidget;
	QHBoxLayout* layout = new QHBoxLayout{ this->user };
	this->userEventList = new QListWidget{};
	this->userEventList->setSelectionMode(QAbstractItemView::SingleSelection);
	layout->addWidget(this->userEventList);
	QWidget* rightSide = new QWidget{};
	QVBoxLayout* vLayout = new QVBoxLayout{ rightSide };
	QWidget* eventDataWidget = new QWidget{};
	QFormLayout* formLayout = new QFormLayout{ eventDataWidget };
	this->userTitleEdit = new QLineEdit{};
	this->userTitleEdit->setReadOnly(true);
	this->userDescriptionEdit = new QTextEdit{};
	this->userDescriptionEdit->setReadOnly(true);
	this->userDateEdit = new QLineEdit{};
	this->userDateEdit->setReadOnly(true);
	this->userTimeEdit = new QLineEdit{};
	this->userTimeEdit->setReadOnly(true);
	this->userParticipantsEdit = new QLineEdit{};
	this->userParticipantsEdit->setReadOnly(true);
	this->userLinkEdit = new QTextEdit{};
	this->userLinkEdit->setReadOnly(true);
	QFont f{ "Corbel Light", 16 };
	QLabel* titleLabel = new QLabel{ "&Event Title:" };
	titleLabel->setBuddy(this->userTitleEdit);
	QLabel* descriptionLabel = new QLabel{ "&Event Description:" };
	descriptionLabel->setBuddy(this->userDescriptionEdit);
	QLabel* dateLabel = new QLabel{ "&Event Date:" };
	dateLabel->setBuddy(this->userDateEdit);
	QLabel* timeLabel = new QLabel{ "&Event Time:" };
	timeLabel->setBuddy(this->userTimeEdit);
	QLabel* participantsLabel = new QLabel{ "&Event Participants:" };
	participantsLabel->setBuddy(this->userParticipantsEdit);
	QLabel* linkLabel = new QLabel{ "&Event Link:" };
	linkLabel->setBuddy(this->userLinkEdit);
	titleLabel->setFont(f);
	descriptionLabel->setFont(f);
	dateLabel->setFont(f);
	timeLabel->setFont(f);
	participantsLabel->setFont(f);
	linkLabel->setFont(f);
	this->userTitleEdit->setFont(f);
	this->userDescriptionEdit->setFont(f);
	this->userDateEdit->setFont(f);
	this->userTimeEdit->setFont(f);
	this->userParticipantsEdit->setFont(f);
	this->userLinkEdit->setFont(f);
	formLayout->addRow(titleLabel, this->userTitleEdit);
	formLayout->addRow(descriptionLabel, this->userDescriptionEdit);
	formLayout->addRow(dateLabel, this->userDateEdit);
	formLayout->addRow(timeLabel, this->userTimeEdit);
	formLayout->addRow(participantsLabel, this->userParticipantsEdit);
	formLayout->addRow(linkLabel, this->userLinkEdit);
	vLayout->addWidget(eventDataWidget);

	QWidget* buttonsWidget = new QWidget{};
	QHBoxLayout* hLayout = new QHBoxLayout{ buttonsWidget };
	this->deleteEventButton = new QPushButton("Delete Event");
	this->deleteEventButton->setFont(f);
	this->goToPage = new QPushButton("Go To Page");
	this->goToPage->setFont(f);
	this->open = new QPushButton("Open file");
	this->open->setFont(f);
	this->undo = new QPushButton("Undo");
	this->undo->setFont(f);
	this->redo = new QPushButton("Redo");
	this->redo->setFont(f);

	hLayout->addWidget(this->deleteEventButton);
	hLayout->addWidget(this->goToPage);
	hLayout->addWidget(this->open);
	hLayout->addWidget(this->undo);
	hLayout->addWidget(this->redo);
	vLayout->addWidget(buttonsWidget);

	layout->addWidget(this->userEventList);
	layout->addWidget(rightSide);
	this->u = new QShortcut(this->user);
	this->u->setKey(QKeySequence("Ctrl+Z"));
	this->r = new QShortcut(this->user);
	this->r->setKey(QKeySequence("Ctrl+Y"));
	this->service.restart();
	this->connectSignalsAndSlotsPersonal();
	this->populateUserEventList();
	this->user->show();
}


void userGUI::connectSignalsAndSlotsPersonal()
{
	QObject::connect(this->userEventList, &QListWidget::itemSelectionChanged, this, [this]() {this->listItemChangedUser(); });
	QObject::connect(this, &userGUI::eventsUpdatedSignal, this, &userGUI::populateUserEventList);
	QObject::connect(this->deleteEventButton, &QPushButton::clicked, this, &userGUI::deleteEventButtonHandler);
	QObject::connect(this->goToPage, &QPushButton::clicked, this, &userGUI::openURL);
	QObject::connect(this->open, &QPushButton::clicked, this, &userGUI::openFile);
	QObject::connect(this->undo, &QPushButton::clicked, this, &userGUI::undoAction);
	QObject::connect(this->redo, &QPushButton::clicked, this, &userGUI::redoAction);
	QObject::connect(this->u, &QShortcut::activated, this, &userGUI::undoAction);
	QObject::connect(this->r, &QShortcut::activated, this, &userGUI::redoAction);

}

void userGUI::deleteEventButtonHandler()
{
	int idx = this->getSelectedIndexUser();

	if (idx < 0 || idx >= this->service.userEventList().size())
		return;

	std::vector<Event> events = this->service.userEventList();
	std::string title = events[idx].getTitle();

	this->service.removeEventUser(title);

	emit eventsUpdatedSignal();
}

void userGUI::populateUserEventList()
{
	if (this->userEventList->count() > 0)
		this->userEventList->clear();

	std::vector<Event> events = this->service.userEventList();

	for (auto ev : events)
	{
		QString itemInList = QString::fromStdString(ev.getTitle());
		QFont f{ "Corbel Light", 16 };
		QListWidgetItem* item = new QListWidgetItem{ itemInList };
		item->setFont(f);
		this->userEventList->addItem(item);
	}

	if (events.size() > 0)
		this->userEventList->setCurrentRow(0);
}

int userGUI::getSelectedIndexUser()
{
	if (this->userEventList->count() == 0)
		return -1;

	QModelIndexList index = this->userEventList->selectionModel()->selectedIndexes();
	if (index.size() == 0)
	{
		this->userTitleEdit->clear();
		this->userDescriptionEdit->clear();
		this->userDateEdit->clear();
		this->userTimeEdit->clear();
		this->userParticipantsEdit->clear();
		this->userLinkEdit->clear();
		return -1;
	}

	int idx = index.at(0).row();
	return idx;
}

void userGUI::listItemChangedUser()
{
	int idx = this->getSelectedIndexUser();
	if (idx == -1)
		return;

	std::vector<Event> events = this->service.userEventList();

	if (idx >= events.size())
		return;
	Event ev = events[idx];

	this->userTitleEdit->setText(QString::fromStdString(ev.getTitle()));
	this->userDescriptionEdit->setText(QString::fromStdString(ev.getDescription()));
	this->userDateEdit->setText(QString::fromStdString(ev.getDate()));
	this->userTimeEdit->setText(QString::fromStdString(ev.getTime()));
	this->userParticipantsEdit->setText(QString::fromStdString(std::to_string(ev.getParticipants())));
	this->userLinkEdit->setText(QString::fromStdString(ev.getLink()));


}


void userGUI::openURL()
{
	QDesktopServices::openUrl(QUrl{ this->userLinkEdit->toPlainText() });
}

void userGUI::openFile()
{
	ShellExecuteA(NULL, "open", this->filename.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void userGUI::undoAction()
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

void userGUI::redoAction()
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
