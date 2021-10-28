#include"GUITableView.h"
#include <QTableView>

GUITableView::GUITableView(Repository& repo, const std::string& type, QWidget* parent) : repo{ repo }, type{ type }, QMainWindow{ parent }
{
	this->tableModel = new EditableEventsTableModel{this->repo};
	this->setUpTableView();
}

GUITableView::~GUITableView()
{
}


void GUITableView::decrease(int position)
{
	this->tableModel->removeRow(position, QModelIndex());
}

void GUITableView::setUpTableView()
{
	QTableView* tableview = new QTableView{};
	this->setCentralWidget(tableview);
	tableview->setModel(this->tableModel);
	tableview->setSortingEnabled(true);
	tableview->setAlternatingRowColors(true);
	tableview->resizeColumnsToContents();
}
