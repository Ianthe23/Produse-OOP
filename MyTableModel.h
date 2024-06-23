#pragma once

#include <QAbstractTableModel>
#include <QAbstractItemView>
#include <vector>

#include "domain.h"

using std::vector;

class MyTableModel :public QAbstractTableModel {
	vector<Produs> produse;
	vector<int> vocale;
	int nr;

public:
	MyTableModel(const vector<Produs>& produse, const vector<int> vocale, int nr) {
		this->produse = produse;
		this->vocale = vocale;
		this->nr = nr;
	}

	int rowCount(const QModelIndex& parent = QModelIndex{}) const override {
		return produse.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex{}) const override {
		return 5;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::BackgroundRole) {
			auto p = produse[index.row()];
			double pret = p.getPret();
			if (pret <= nr) {
				QBrush bg(Qt::darkRed);
				return bg;
			}
		}
		if (role == Qt::DisplayRole) {
			const Produs& p = produse[index.row()];
			switch (index.column()) {
			case 0:
				return QString::number(p.getId());
			case 1:
				return QString::fromStdString(p.getNume());
			case 2:
				return QString::fromStdString(p.getTip());
			case 3:
				return QString::number(p.getPret()).toDouble();
			case 4:
				return QString::number(vocale[index.row()]);
			}
		}
		return QVariant();
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
			switch (section) {
			case 0:
				return "ID";
			case 1:
				return "Nume";
			case 2:
				return "Tip";
			case 3:
				return "Pret";
			case 4:
				return "Nr. vocale din nume";
			default:
				return QString("");
			}
		}
		return QVariant();
	}

	void setProduse(const vector<Produs> produse, vector<int> vocale, int nr) {
		this->produse = produse;
		this->vocale = vocale;
		this->nr = nr;
		auto topLeft = createIndex(0, 0);
		auto bottomRight = createIndex(rowCount(), columnCount());
		emit layoutChanged();
		emit dataChanged(topLeft, bottomRight);
	}
};
