//
// Created by Mircea Maierean on 12.06.2023.
//

#ifndef STARS_ASTRONAUTWINDOW_H
#define STARS_ASTRONAUTWINDOW_H

#include "Service.h"
#include <QWidget>
#include <utility>
#include <QTableView>
#include <QCheckBox>
#include <QSortFilterProxyModel>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include "starsModels.h"

class AstronautWindow : public QWidget {
private:
    QCheckBox* constellations{};
    Astronaut aust;
    Service &service;
    QTableView *table;
    starsModel *stars;
    QSortFilterProxyModel *model;
    QLineEdit *nameOfStarLineEdit, *raEdit, *decEdit, *starNameFilter;
    QPushButton *addStarButton;
    QListWidget *filteredStars;
public:
    AstronautWindow(Astronaut aust, Service &service, starsModel * model);
public slots:
    void setup();
    void showConstellationsFiltered();
    void addStar();
    void populateList();
};


#endif //STARS_ASTRONAUTWINDOW_H
