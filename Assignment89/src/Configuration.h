#pragma once
#include <qwidget.h>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QCloseEvent>

class Config : public QDialog
{
	Q_OBJECT

public:
	Config(QWidget* parent = 0);
	~Config();


private:
	std::string sourcefile;
	std::string displayfile;
	QPushButton* file;
	QLineEdit* path;
	QPushButton* ok;
	QRadioButton* csvButton;
	QRadioButton* htmlButton;

public:
	void openFile();
	std::string getOption();

};

