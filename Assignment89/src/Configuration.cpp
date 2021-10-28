#include "Configuration.h"
#include <QFileDialog>


Config::Config(QWidget* parent)
{
	QVBoxLayout* layout = new QVBoxLayout{ this };
	QWidget* fileWidget = new QWidget{};
	QFormLayout* fileLayout = new QFormLayout{ fileWidget };
	QFont f{ "Corbel Light", 10 };
	QLabel* prompt = new QLabel(tr("&Open source file "));
	this->path = new QLineEdit;
	this->file = new QPushButton(tr("File..."));
	prompt->setBuddy(this->path);
	prompt->setFont(f);
	this->file->setFont(f);
	fileLayout->addRow(prompt, this->path);
	fileLayout->addWidget(this->file);
	QWidget* filesWidget = new QWidget{};
	QFormLayout* filesLayout = new QFormLayout{ filesWidget };
	QLabel* csv = new QLabel(tr("&CSV file "));
	csv->setFont(f);
	this->csvButton = new QRadioButton;
	csv->setBuddy(csvButton);
	filesLayout->addRow(csv, this->csvButton);
	QLabel* html = new QLabel(tr("&HTML file "));
	html->setFont(f);
	this->htmlButton = new QRadioButton;
	html->setBuddy(this->htmlButton);
	filesLayout->addRow(html, this->htmlButton);
	this->ok = new QPushButton(tr("OK"));
	layout->addWidget(fileWidget);
	layout->addWidget(filesWidget);
	layout->addWidget(this->ok);
	connect(this->file, &QPushButton::clicked, this, &Config::openFile);
	connect(this->ok, &QPushButton::clicked, this, &Config::close);
}


Config::~Config()
{

}

void Config::openFile()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open source file"), "D:\OOPgithub\a89-912-Crismariu-Ioana\Assignment89", tr("Text Files (*.txt)"));
	this->path->setText(filename);
	this->sourcefile = filename.toStdString();
}

std::string Config::getOption()
{
	if (this->csvButton->isChecked())
		return "CSV";
	else if (this->htmlButton->isChecked())
		return "HTML";
}

