//
// Created by Mircea Maierean on 12.06.2023.
//

#include "starsModels.h"

int starsModel::rowCount(const QModelIndex &parent) const {
    return this->repository.getStars().size();
}

int starsModel::columnCount(const QModelIndex &parent) const {
    return 4;
}

QVariant starsModel::data(const QModelIndex &index, int role) const {
    int row = index.row(), column = index.column();
    Star star = this->repository.getStars()[row];
    if (role == Qt::DisplayRole)
        switch(column)
        {
            case 0:
                return QString::fromStdString(star.getName());
            case 1:
                return QString::fromStdString(star.getConstellation());
            case 2:
                return QString::fromStdString(std::to_string(star.getRa()));
            case 3:
                return QString::fromStdString(std::to_string(star.getDec()));
        }
    return QVariant();
}

QVariant starsModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
            case 0:
                return "Name of Star";
            case 1:
                return "Constellation";
            case 2:
                return "RA";
            case 3:
                return "Dec";
        }
    }
    return QVariant();
}

void starsModel::updateData() {
    beginResetModel();
    endResetModel();
    emit this->dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}