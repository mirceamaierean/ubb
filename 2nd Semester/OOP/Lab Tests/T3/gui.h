//
// Created by Mircea Maierean on 25.05.2023.
//

#ifndef T3_914MAIEREANMIRCEA_GUI_H
#define T3_914MAIEREANMIRCEA_GUI_H

#include "Service.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class GUI : public QWidget
{
private:
    Service service;
    QListWidget *listWidgetWithDocuments;
    QLabel *searchDocumentsLabel;
    QLineEdit *lineEditForSearch;
    QLabel *bestMatchLabel;
    QLineEdit *bestMatchInput;
    QPushButton *bestMatchButton;
    QLineEdit *bestMatch;

public:
    explicit GUI(QWidget *parent = Q_NULLPTR);
    void loadDocuments();

public slots:
    void filterList();
    void findBestMatch();
};

#endif //T3_914MAIEREANMIRCEA_GUI_H
