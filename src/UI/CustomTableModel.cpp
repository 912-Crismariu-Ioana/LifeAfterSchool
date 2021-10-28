#include "CustomTableModel.h"
#include <QFont>
#include <QBrush>

EventsTableModel::EventsTableModel(Service& r, const std::string& type, QObject* parent) : QAbstractTableModel{ parent }, type{type}, srv{r}
{

}

EventsTableModel::~EventsTableModel()
{
}

int EventsTableModel::rowCount(const QModelIndex& parent) const
{
	int eventsNumber;
	if (this->type == "admin")
		eventsNumber = this->srv.adminEventsSize();
	else
		eventsNumber = this->srv.userEventsSize();
	return eventsNumber;
}

int EventsTableModel::columnCount(const QModelIndex& parent) const
{
	return 6;
}

QVariant EventsTableModel::data(const QModelIndex& index, int role) const
{
	
	int row = index.row();
	int column = index.column();
	std::vector<Event> events;
	if (this->type == "admin")
		events = this->srv.eventList();
	else
		events = this->srv.userEventList();

	if (row == events.size())
	{
		return QVariant();
	}
	

	Event g = events[row];

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(g.getTitle());
		case 1:
			return QString::fromStdString(g.getDescription());
		case 2:
			return QString::fromStdString(g.getDate());
		case 3:
			return QString::fromStdString(g.getTime());
		case 4:
			return QString::fromStdString(std::to_string(g.getParticipants()));
		case 5:
			return QString::fromStdString(g.getLink());
		default:
			break;
		}
	}
	if (role == Qt::FontRole)
	{
		QFont font("Corbel Light", 15, 10, true);
		font.setItalic(false);
		return font;
	}
	if (role == Qt::BackgroundRole)
	{
		if (row % 2 == 1)
		{
			return QBrush{ QColor{0, 250, 154} };
		}
	}

	return QVariant{};
}

QVariant EventsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString{ "Event title" };
			case 1:
				return QString{ "Event description" };
			case 2:
				return QString{ "Event date" };
			case 3:
				return QString{ "Event time" };
			case 4:
				return QString{ "Event participants" };
			case 5:
				return QString{ "Event link" };
			default:
				break;
			}
		}
	}
	if (role == Qt::FontRole)
	{
		QFont font("Corbel Light", 15, 10, true);
		font.setBold(true);
		font.setItalic(false);
		return font;
	}

	return QVariant{};
}


bool EventsTableModel::insertRows(int position, int rows, const QModelIndex& parent)
{

	beginInsertRows(QModelIndex(), position, position + rows - 1);
	endInsertRows();
	return true;
}


bool EventsTableModel::removeRows(int position, int rows, const QModelIndex& parent)
{
	beginRemoveRows(QModelIndex(), position, position + rows - 1);
    endRemoveRows();
	return true;
}

