#pragma once

#include <QtWidgets/QMainWindow>
#include "EditableCustomTableModel.h"


class GUITableView : public QMainWindow
{
	Q_OBJECT

private:
	Repository& repo;
	std::string type;
	EditableEventsTableModel* tableModel;
public:
	GUITableView(Repository& repo, const std::string& type, QWidget* parent = 0);
	~GUITableView();
	void decrease(int position);
	void setUpTableView();
};

