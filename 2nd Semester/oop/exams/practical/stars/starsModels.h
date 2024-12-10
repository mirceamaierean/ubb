//
// Created by Mircea Maierean on 12.06.2023.
//

#ifndef STARS_STARSMODELS_H
#define STARS_STARSMODELS_H

#include "Repository.h"
#include <QAbstractTableModel>

class starsModel : public QAbstractTableModel
{
private:
    Repository &repository;
public:
    explicit starsModel(Repository &repository) : repository(repository) {}
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void updateData();
};


#endif //STARS_STARSMODELS_H
