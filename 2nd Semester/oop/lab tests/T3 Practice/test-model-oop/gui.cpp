//
// Created by Mircea Maierean on 24.05.2023.
//

#include "gui.h"

GUI::GUI(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    this->setWindowTitle("Car shop");
    this->listWidgetAllCars = new QListWidget();
    this->listWidgetFilteredCars = new QListWidget();
    this->searchByManufacturerLineEdit = new QLineEdit();
    this->searchByManufacturerButton = new QPushButton("Search after manufacturer");
    this->numberOfCarsLabel = new QLabel("Number of cars: ");
    mainLayout->addWidget(this->listWidgetAllCars);
    mainLayout->addWidget(this->searchByManufacturerLineEdit);
    mainLayout->addWidget(this->searchByManufacturerButton);
    mainLayout->addWidget(this->numberOfCarsLabel);
    mainLayout->addWidget(this->listWidgetFilteredCars);
    this->setLayout(mainLayout);
    this->populateListWidgetAllCars();
    QObject::connect(this->searchByManufacturerButton, &QPushButton::clicked, this, &GUI::searchByManufacturer);
    QObject::connect(this->searchByManufacturerLineEdit, &QLineEdit::textChanged, this, &GUI::searchByManufacturer);
    QObject::connect(this->searchByManufacturerLineEdit, &QLineEdit::returnPressed, this, &GUI::searchByManufacturer);
}

void GUI::populateListWidgetAllCars() {
    this->listWidgetAllCars->clear();
    for (auto car: this->service.getAllCars()) {
        this->listWidgetAllCars->addItem(QString::fromStdString(car.toString()));
        this->listWidgetAllCars->item(this->listWidgetAllCars->count() - 1)->setForeground(
                QColor(QString::fromStdString(car.getColour())));
    }
}

void GUI::searchByManufacturer()
{
    std::string manufacturer = this->searchByManufacturerLineEdit->text().toStdString();
    this->listWidgetFilteredCars->clear();
    std::vector<Car> filteredCars = this->service.getCarsByManufacturer(manufacturer);
    for (auto car : filteredCars)
        this->listWidgetFilteredCars->addItem(QString::fromStdString(car.toString()));
    this->numberOfCarsLabel->setText(QString::fromStdString("Number of cars: " + std::to_string(filteredCars.size())));
}