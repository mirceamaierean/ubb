//
// Created by Mircea Maierean on 24.05.2023.
//

#include "gui.h"

GUI::GUI(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout;
    this->listWithTasks = new QListWidget;
    this->labelForPriority = new QLabel("Enter Priority");
    this->priorityOfTask = new QLineEdit;
    this->resultOfPriority = new QLabel("Total Duration");
    this->computeResultButton = new QPushButton("Show Duration");
    this->resultOfPrioritiesOfTasks = new QLineEdit;
    this->listWithTasksWithGivenPriority = new QListWidget;

    mainLayout->addWidget(this->listWithTasks);
    mainLayout->addWidget(this->labelForPriority);
    mainLayout->addWidget(this->priorityOfTask);
    mainLayout->addWidget(this->computeResultButton);
    mainLayout->addWidget(this->resultOfPriority);
    mainLayout->addWidget(this->resultOfPrioritiesOfTasks);
    mainLayout->addWidget(this->listWithTasksWithGivenPriority);

    this->setLayout(mainLayout);
    this->populateListWithTasks();

    QObject::connect(this->computeResultButton, &QPushButton::clicked, this, &GUI::computeDuration);
    QObject::connect(this->priorityOfTask, &QLineEdit::returnPressed, this, &GUI::computeDuration);
}

void GUI::populateListWithTasks() {
    this->listWithTasks->clear();
    for (auto task: this->service.getAllTasks()) {
        this->listWithTasks->addItem(QString::fromStdString(task.toString()));
        if (task.getPriority() == 1)
            this->listWithTasks->item(this->listWithTasks->count() - 1)->setFont(QFont("Arial", 12, QFont::ExtraBold));
    }
}

void GUI::computeDuration() {
    int priority = this->priorityOfTask->text().toInt(), duration = 0;
    std::vector<Task> tasks = this->service.getTasksWithGivenPriority(priority);
    this->listWithTasksWithGivenPriority->clear();
    for (auto task: tasks) {
        this->listWithTasksWithGivenPriority->addItem(QString::fromStdString(task.toString()));
        duration += task.getEstimatedDuration();
    }
    if (duration == 0)
        this->resultOfPrioritiesOfTasks->setText("No tasks with given priority");
    else
        this->resultOfPrioritiesOfTasks->setText(QString::number(duration));
}