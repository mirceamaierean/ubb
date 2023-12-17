//
// Created by Mircea Maierean on 24.05.2023.
//

#ifndef TASK_MANAGER_GUI_H
#define TASK_MANAGER_GUI_H

#include "service.h"
#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>

class GUI : public QWidget{
private:
    Service service;
    QListWidget *listWithTasks;
    QListWidget *listWithTasksWithGivenPriority;
    QLabel *labelForPriority;
    QLineEdit *priorityOfTask;
    QLabel *resultOfPriority;
    QLineEdit *resultOfPrioritiesOfTasks;
    QPushButton *computeResultButton;
public:
    GUI(QWidget *parent = Q_NULLPTR);
    void populateListWithTasks();
public slots:
    void computeDuration();
};

#endif //TASK_MANAGER_GUI_H


