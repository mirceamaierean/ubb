//
// Created by Mircea Maierean on 25.05.2023.
//

#ifndef BILLS_GUI_H
#define BILLS_GUI_H
#include "service.h"
#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class GUI : public QWidget{
private:
    Service service;
    QListWidget *billsListWidget;
    QPushButton *sortBills;
    QLabel *userInputLabel;
    QLineEdit *userInput;
    QPushButton *calculateAmountOfUnpaidBill;
    QLabel *calculateAmountLabel;
    QLineEdit *totalAmount;
public:
    GUI(QWidget *parent = Q_NULLPTR);
    void loadBills();
public slots:
    void loadSortedBills();
    void showAmountOfBills();
};

#endif //BILLS_GUI_H
