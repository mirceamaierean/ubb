//
// Created by Mircea Maierean on 24.05.2023.
//

#ifndef TEST_MODEL_OOP_GUI_H
#define TEST_MODEL_OOP_GUI_H
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include "service.h"

class GUI : public QWidget
{
private:
    Service service;
    QListWidget* listWidgetAllCars;
    QListWidget *listWidgetFilteredCars;
    QLineEdit *searchByManufacturerLineEdit;
    QPushButton *searchByManufacturerButton;
    QLabel *numberOfCarsLabel;
public:
    GUI(QWidget* parent = Q_NULLPTR);
    void populateListWidgetAllCars();
    public slots:
    void searchByManufacturer();
};

#endif //TEST_MODEL_OOP_GUI_H
