//
// Created by Mircea Maierean on 14.06.2023.
//

#ifndef PRACTIC_WINDOW_H
#define PRACTIC_WINDOW_H

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

class Window : public Observer, public QWidget {
private:
    Session &session;
    Department department;
    QLabel *description;
    QListWidget *volunteersList, *unassignedVolunteers;
    QPushButton *addVolunteer, *assignVolunteer, *mostSuitable;
    QLineEdit *volunteerName, *volunteerEmail, *volunteerInterests;
    QLabel *volunteerNameLabel, *volunteerEmailLabel, *volunteerInterestsLabel;

public:
    Window(Session &session, Department department, QWidget *parent = nullptr);
    void update() override;
public slots:
    void addVol();
    void assignVol();
    void displayMostSuitable();
};


#endif //PRACTIC_WINDOW_H
