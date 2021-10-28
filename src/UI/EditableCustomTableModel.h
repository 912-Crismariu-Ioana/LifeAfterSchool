#pragma once
#include <QAbstractTableModel>
#include "Repository.h"

class EditableEventsTableModel : public QAbstractTableModel
{
private: 
	Repository& repo;

public:
	EditableEventsTableModel(Repository& r, QObject* parent = NULL);
	~EditableEventsTableModel();

	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
	int columnCount(const QModelIndex& parent = QModelIndex{}) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
	bool removeRows(int position, int rows, const QModelIndex& parent) override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;

};
