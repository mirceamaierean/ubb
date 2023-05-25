//
// Created by Mircea Maierean on 24.05.2023.
//

#ifndef VEGETABLES_GUI_H
#define VEGETABLES_GUI_H
#include "service.h"
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class GUI : public QWidget
{
private:
    Service service;
    QListWidget *listWithFamilies;
    QListWidget *listWithVegetables;
    QLabel *labelForVegetable;
    QPushButton *searchButton;
    QLineEdit *consumableParts;
    QLineEdit *searchVegetableLine;
public:
    GUI(QWidget *parent = Q_NULLPTR);
    void populateListWithFamilies();
public slots:
    void populateListWithVegetables();
    void searchVegetable();
};


#endif //VEGETABLES_GUI_H
