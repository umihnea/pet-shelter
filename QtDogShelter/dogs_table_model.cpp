#include "dogs_table_model.h"

QVariant DogsTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal && 0 <= section && section < table_header.size())
		return table_header[section];
	return QVariant();
}

QVariant DogsTableModel::data(const QModelIndex & index, int role) const {
	auto dog = repo.get(index.row());
	if (role == Qt::DisplayRole || role == Qt::EditRole)
		switch (index.column()) {
			case 0: return QString::fromStdString(dog.get_name());
			case 1: return QString::fromStdString(dog.get_breed());
			case 2: return QString::number(dog.get_age());
			case 3: return QString::fromStdString(dog.get_image());
			default: break;
		}
	return QVariant();
}

bool DogsTableModel::setData(const QModelIndex & index, const QVariant & value, int role) {
	if (!index.isValid() || role != Qt::EditRole)
		return false;

	int row = index.row(), col = index.column();
	Dog& dog = repo.get_collection()[index.row()];

	//if (role != Qt::EditRole) return false;

	if (role == Qt::EditRole) {
		switch (col) {
			case 0: {
				std::string dog_name{ value.toString().toStdString() };
				dog.set_name(dog_name);
				break;
			}
			case 1: {
				std::string dog_breed{ value.toString().toStdString() };
				dog.set_breed(dog_breed);
				break;
			}
			case 2: {
				int age{ value.toInt() };
				dog.set_age(age);
				break;
			}
			case 3: {
				std::string url{ value.toString().toStdString() };
				dog.set_image(url);
				break;
			}
		}
	}

	emit dataChanged(index, index);
	return true;
}

Qt::ItemFlags DogsTableModel::flags(const QModelIndex & index) const {
	return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;
}
