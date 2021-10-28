#include "EditableCustomTableModel.h"
#include <QFont>
#include <QBrush>

EditableEventsTableModel::EditableEventsTableModel(Repository& r, QObject* parent) : QAbstractTableModel{ parent }, repo{ r }
{
}

EditableEventsTableModel::~EditableEventsTableModel()
{
}

int EditableEventsTableModel::rowCount(const QModelIndex& parent) const
{

	int genesNumber = this->repo.len();
	return genesNumber+1;
}

int EditableEventsTableModel::columnCount(const QModelIndex& parent) const
{
	return 6;
}

QVariant EditableEventsTableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();

	std::vector<Event> events = this->repo.getAll();

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

QVariant EditableEventsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

bool EditableEventsTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (!index.isValid() || role != Qt::EditRole)
		return false;

	int eventIndex = index.row();

	std::vector<Event> events = this->repo.getAll();


	if (eventIndex == events.size())
	{
		this->beginInsertRows(QModelIndex{}, eventIndex, eventIndex);

		switch (index.column())
		{
		case 0:
			this->repo.addEvent(Event{ value.toString().toStdString(), " ", " ", " " , 0, " " });
			break;
		case 1:
			this->repo.addEvent(Event{ " ", value.toString().toStdString(), " ", " ",  0, " " });
			break;
		case 2:
			this->repo.addEvent(Event{ " ", " ", value.toString().toStdString(), " ", 0, " " });
			break;
		case 3:
			this->repo.addEvent(Event{ " ", " ", " ", value.toString().toStdString(), 0, " " });
			break;
		case 4:
			this->repo.addEvent(Event{ "", "", "", "", stoi(value.toString().toStdString()), "" });
			break;
		case 5:
			this->repo.addEvent(Event{ "", "", "", "", 0, value.toString().toStdString() });
			break;

		}

		this->endInsertRows();
		return true;
	}

	Event& currentEvent = events[eventIndex];
	switch (index.column())
	{
	case 0:
		currentEvent.setTitle(value.toString().toStdString());
		break;
	case 1:
		currentEvent.setDescription(value.toString().toStdString());
		break;
	case 2:
		currentEvent.setDate(value.toString().toStdString());
		break;
	case 3:
		currentEvent.setTime(value.toString().toStdString());
		break;
	case 4:
		currentEvent.setParticipants(stoi(value.toString().toStdString()));
		break;
	case 5:
		currentEvent.setLink(value.toString().toStdString());
		break;

	}
	Event& ev = this->repo.findByTitle(currentEvent.getTitle());
	this->repo.updateEvent(ev, currentEvent.getLink(), currentEvent.getDescription(), currentEvent.getDate(), currentEvent.getTime(), currentEvent.getParticipants());

	// emit the dataChanged signal
	emit dataChanged(index, index);

	return true;
}

bool EditableEventsTableModel::removeRows(int position, int rows, const QModelIndex& parent)
{
	beginRemoveRows(QModelIndex(), position, position + rows - 1);
	endRemoveRows();
	return true;
}

Qt::ItemFlags EditableEventsTableModel::flags(const QModelIndex& index) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}