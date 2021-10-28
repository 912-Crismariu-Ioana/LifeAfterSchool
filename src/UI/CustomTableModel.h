#pragma once

#include <QAbstractTableModel>
#include "Service.h"

class EventsTableModel : public QAbstractTableModel
{
private:
	Service& srv;
	std::string type;

public:
	EventsTableModel(Service& r, const std::string& type, QObject* parent = NULL);
	~EventsTableModel();

	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
	int columnCount(const QModelIndex& parent = QModelIndex{}) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	bool insertRows(int position, int rows, const QModelIndex& parent) override;
	bool removeRows(int position, int rows, const QModelIndex& parent) override;
};
