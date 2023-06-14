//
// Created by Mircea Maierean on 14.06.2023.
//

#include "stats.h"

Statistics::Statistics(Session &session, QWidget *parent) : session{session}, QWidget(parent) {
    this->session.registerObserver(this);
    this->setWindowTitle("Stats");

    auto *layout = new QVBoxLayout();

    this->departmentsAndVolunteers = new QListWidget();
    layout->addWidget(this->departmentsAndVolunteers);

    this->setLayout(layout);

    this->update();
}

void Statistics::update()
{
     this->departmentsAndVolunteers->clear();

     for (auto &department : this->session.getStatistics())
     {
         auto *item = new QListWidgetItem(QString::fromStdString(department.second + " " + to_string(department.first)));
         this->departmentsAndVolunteers->addItem(item);
     }
}