//
// Created by Mircea Maierean on 13.06.2023.
//

#include "Window.h"
#include <QVBoxLayout>
#include <QMessageBox>

Window::Window(Session &session, Person &currentPerson, QWidget *parent) : session{session}, currentPerson{currentPerson}, QWidget(parent)
{
    this->session.registerObserver(this);
    this->setWindowTitle(QString::fromStdString(this->currentPerson.getName() + " " + this->currentPerson.getRole()));

    auto *layout = new QVBoxLayout(this);
    this->issuesList = new QListWidget(this);

    for (const auto &issue : this->session.getIssues())
        this->issuesList->addItem(QString::fromStdString(issue.formatAsString()));

    layout->addWidget(this->issuesList);
    this->setLayout(layout);

    this->removeIssueButton = new QPushButton("Remove issue", this);
    layout->addWidget(removeIssueButton);

    QObject::connect(this->removeIssueButton, &QPushButton::clicked, this, &Window::removeIssue);

    if (this->currentPerson.getRole() == "Tester")
    {
        this->addIssueButton = new QPushButton("Add issue", this);
        this->descriptionInput = new QLineEdit();
        layout->addWidget(this->addIssueButton);
        layout->addWidget(this->descriptionInput);
        QObject::connect(this->addIssueButton, &QPushButton::clicked, this, &Window::addIssue);
    }
    else if (this->currentPerson.getRole() == "Programmer")
    {
        this->resolveIssueButton = new QPushButton("Resolve issue", this);
        this->resolveIssueButton->setEnabled(false);
        layout->addWidget(this->resolveIssueButton);
        QObject::connect(this->issuesList, &QListWidget::clicked, this, &Window::updateResolveButton);
        QObject::connect(this->resolveIssueButton, &QPushButton::clicked, this, &Window::resolveIssue);
    }
}

void Window::update() const
{
    this->issuesList->clear();
    for (const auto &issue : this->session.getIssues())
        this->issuesList->addItem(QString::fromStdString(issue.formatAsString()));
}

void Window::removeIssue()
{
    int currentRow = this->issuesList->currentRow();
    if (this->session.getIssues()[currentRow].getIsOpen())
        QMessageBox::critical((QWidget *) this, "Error", "Invalid Selection");
    else
        this->session.removeIssue(currentRow);
}

void Window::addIssue() {
    std::string description = this->descriptionInput->text().toStdString();
    bool status = true;
    std::string reporter = this->currentPerson.getName();
    std::string solver = "";
    try {
        this->session.addIssue(description, status, reporter, solver);
    } catch (std::exception &e) {
        QMessageBox::critical((QWidget *) this, "Error", e.what());
    }
}

void Window::updateResolveButton()
{
    if (this->session.getIssues()[this->issuesList->currentRow()].getIsOpen())
        this->resolveIssueButton->setEnabled(true);
    else
        this->resolveIssueButton->setEnabled(false);
}

void Window::resolveIssue()
{
    int currentRow = this->issuesList->currentRow();
    std::string solver = this->currentPerson.getName();
    this->session.resolveIssue(currentRow, solver);
    this->resolveIssueButton->setEnabled(false);
}
