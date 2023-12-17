//
// Created by Mircea Maierean on 14.06.2023.
//

#include "window.h"
#include <QMessageBox>

Window::Window(Session &session, Department department, QWidget *parent) : session{session}, department(department), QWidget(parent) {
    this->session.registerObserver(this);
    this->setWindowTitle(QString::fromStdString(department.getName()));

    auto *layout = new QVBoxLayout();

    this->description = new QLabel(QString::fromStdString("Description: " + department.getDescription()));
    layout->addWidget(this->description);


    auto *layoutLists = new QHBoxLayout();
    this->volunteersList = new QListWidget();
    layoutLists->addWidget(this->volunteersList);

    this->unassignedVolunteers = new QListWidget();
    layoutLists->addWidget(this->unassignedVolunteers);

    auto *layoutVolunteer = new QHBoxLayout();

    this->volunteerNameLabel = new QLabel("Name");
    layoutVolunteer->addWidget(this->volunteerNameLabel);

    this->volunteerName = new QLineEdit();
    layoutVolunteer->addWidget(this->volunteerName);

    this->volunteerEmailLabel = new QLabel("Email");
    layoutVolunteer->addWidget(this->volunteerEmailLabel);

    this->volunteerEmail = new QLineEdit();
    layoutVolunteer->addWidget(this->volunteerEmail);

    this->volunteerInterestsLabel = new QLabel("Interests");

    layoutVolunteer->addWidget(this->volunteerInterestsLabel);

    this->volunteerInterests = new QLineEdit();
    layoutVolunteer->addWidget(this->volunteerInterests);

    this->addVolunteer = new QPushButton("Add");
    layoutVolunteer->addWidget(this->addVolunteer);

    layout->addLayout(layoutLists);
    layout->addLayout(layoutVolunteer);

    this->assignVolunteer = new QPushButton("Assign");
    layout->addWidget(this->assignVolunteer);

    this->mostSuitable = new QPushButton("Most suitable");
    layout->addWidget(this->mostSuitable);

    this->setLayout(layout);

    this->update();

    QObject::connect(this->addVolunteer, &QPushButton::clicked, this, &Window::addVol);
    QObject::connect(this->assignVolunteer, &QPushButton::clicked, this, &Window::assignVol);
    QObject::connect(this->mostSuitable, &QPushButton::clicked, this, &Window::displayMostSuitable);
}

void Window::update()
{
    this->volunteersList->clear();
    for (auto vol : this->session.getVolunteersFromDepartment(this->department.getName()))
        this->volunteersList->addItem(QString::fromStdString(vol));

    this->unassignedVolunteers->clear();
    for (auto vol : this->session.getUnassigned())
        this->unassignedVolunteers->addItem(QString::fromStdString(vol));
}

void Window::addVol() {
    auto name = this->volunteerName->text().toStdString();
    auto email = this->volunteerEmail->text().toStdString();
    auto interests = this->volunteerInterests->text().toStdString();
    try
    {
        this->session.addVolunteer(name, email, interests, "Unassigned");
        this->volunteerName->clear();
        this->volunteerEmail->clear();
        this->volunteerInterests->clear();
    }
    catch (const std::exception& e)
    {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void Window::assignVol() {
    if (this->unassignedVolunteers->selectedItems().empty())
        return;
    string key = this->unassignedVolunteers->currentItem()->text().toStdString();
    try
    {
        this->session.assignVolunteer(key, this->department.getName());
    }
    catch (const std::exception& e)
    {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void Window::displayMostSuitable() {
    this->unassignedVolunteers->clear();
    for (auto vol : this->session.getMostSuitable(this->department.getDescription()))
        this->unassignedVolunteers->addItem(QString::fromStdString(vol));
}