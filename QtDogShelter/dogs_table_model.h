#pragma once
#include "repo_abstract.h"
#include <QAbstractItemModel>

class DogsTableModel : public QAbstractTableModel {
	Q_OBJECT

private:
	StorageRepo &repo;
	const QStringList table_header{"Dog Name", "Breed", "Age", "Image URL"};

public:
	explicit DogsTableModel(StorageRepo &r) : repo{ r } {}
	~DogsTableModel() {}

	int rowCount(const QModelIndex& parent = QModelIndex{}) const override { return repo.get_size(); }
	int columnCount(const QModelIndex& parent = QModelIndex{}) const override { return 4; }

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
};

