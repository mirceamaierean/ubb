//
// Created by Mircea Maierean on 14.06.2023.
//

#ifndef PRACTIC_STATS_H
#define PRACTIC_STATS_H

#include <QWidget>
#include "observer.h"
#include "session.h"
#include "department.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>

using namespace std;

class Statistics : public Observer, public QWidget {
private:
    Session &session;
    QListWidget *departmentsAndVolunteers;

public:
    Statistics(Session &session, QWidget *parent = nullptr);
    void update() override;
};


#endif //PRACTIC_STATS_H
