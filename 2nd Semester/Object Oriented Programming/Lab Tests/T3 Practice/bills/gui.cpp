//
// Created by Mircea Maierean on 25.05.2023.
//

#include "gui.h"
GUI::GUI(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("Bills");
    QVBoxLayout *mainLayout = new QVBoxLayout;
    this->billsListWidget = new QListWidget;
    this->sortBills = new QPushButton("Sort the bills");
    this->userInputLabel = new QLabel("Enter the name of the company");
    this->userInput = new QLineEdit;
    this->calculateAmountOfUnpaidBill = new QPushButton("Calculate amount of bills");
    this->calculateAmountLabel = new QLabel("Total amount");
    this->totalAmount = new QLineEdit;
    mainLayout->addWidget(billsListWidget);
    mainLayout->addWidget(sortBills);
    mainLayout->addWidget(userInputLabel);
    mainLayout->addWidget(userInput);
    mainLayout->addWidget(calculateAmountOfUnpaidBill);
    mainLayout->addWidget(calculateAmountLabel);
    mainLayout->addWidget(totalAmount);
    this->setLayout(mainLayout);
    this->loadBills();
    QObject::connect(this->sortBills, &QPushButton::clicked, this, &GUI::loadSortedBills);
    QObject::connect(this->calculateAmountOfUnpaidBill, &QPushButton::clicked, this, &GUI::showAmountOfBills);
}

void GUI::loadBills()
{
    this->billsListWidget->clear();
    for (auto bill : this->service.getAllBills())
        this->billsListWidget->addItem(QString::fromStdString(bill.toString()));
}

void GUI::loadSortedBills() {
    this->billsListWidget->clear();
    for (auto bill : this->service.getAllBillsSorted())
        this->billsListWidget->addItem(QString::fromStdString(bill.toString()));
}

void GUI::showAmountOfBills() {
    string company = this->userInput->text().toStdString();
    this->totalAmount->setText(QString::number(this->service.calculateAmountOfBillsFromCompany(company)));
}