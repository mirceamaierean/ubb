//
// Created by Mircea Maierean on 24.05.2023.
//

#include "gui.h"

GUI::GUI(QWidget *parent) : QWidget(parent) {
    this->setWindowTitle("Vegetables");
    QVBoxLayout *mainLayout = new QVBoxLayout;
    this->listWithFamilies = new QListWidget;
    this->listWithVegetables = new QListWidget;
    this->labelForVegetable = new QLabel("Enter the name of the vegetable");
    this->searchButton = new QPushButton("Search For Vegetable");
    this->consumableParts = new QLineEdit;
    this->searchVegetableLine = new QLineEdit;
    mainLayout->addWidget(listWithFamilies);
    mainLayout->addWidget(labelForVegetable);
    mainLayout->addWidget(searchVegetableLine);
    mainLayout->addWidget(searchButton);
    mainLayout->addWidget(listWithVegetables);
    mainLayout->addWidget(consumableParts);
    this->setLayout(mainLayout);
    this->populateListWithFamilies();
    QObject::connect(listWithFamilies, &QListWidget::currentItemChanged, this, &GUI::populateListWithVegetables);
    QObject::connect(searchButton, &QPushButton::clicked, this, &GUI::searchVegetable);
    QObject::connect(searchVegetableLine, &QLineEdit::returnPressed, this, &GUI::searchVegetable);
}

void GUI::populateListWithFamilies() {
    this->listWithFamilies->clear();
    for (auto family : this->service.getFamilies())
        this->listWithFamilies->addItem(QString::fromStdString(family));
    this->listWithVegetables->clear();
}

void GUI::populateListWithVegetables() {
    string family = this->listWithFamilies->currentItem()->text().toStdString();
    this->listWithVegetables->clear();
    for (auto vegetable : this->service.getAllVegetablesBelongingToFamily(family))
        this->listWithVegetables->addItem(QString::fromStdString(vegetable.getName() + " | " + vegetable.getParts()));
}

void GUI::searchVegetable()
{
    Vegetable veg = this->service.getVegetableFromName(this->searchVegetableLine->text().toStdString());
    string family = veg.getFamily();
    this->consumableParts->setText(QString::fromStdString(veg.getParts()));
    for (int i = 0; i < this->listWithFamilies->count(); ++i)
    {
        if (this->listWithFamilies->item(i)->text().toStdString() == family)
            this->listWithFamilies->item(i)->setForeground(QColor(QString::fromStdString("Red")));
        else
            this->listWithFamilies->item(i)->setForeground(QColor(QString::fromStdString("White")));
    }
}