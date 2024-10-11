//
// Created by Mircea Maierean on 25.05.2023.
//

#include "gui.h"

GUI::GUI(QWidget *parent) : QWidget(parent)
{
    auto *mainLayout = new QVBoxLayout;

    this->setWindowTitle("Documents app");
    this->setFixedWidth(350);
    this->listWidgetWithDocuments = new QListWidget;
    this->searchDocumentsLabel = new QLabel("Search for Documents");
    this->lineEditForSearch = new QLineEdit;
    this->bestMatchLabel = new QLabel("Find best match");
    this->bestMatchInput = new QLineEdit;
    this->bestMatchButton = new QPushButton("Show best matching");
    this->bestMatch = new QLineEdit;

    mainLayout->addWidget(listWidgetWithDocuments);
    mainLayout->addWidget(searchDocumentsLabel);
    mainLayout->addWidget(lineEditForSearch);
    mainLayout->addWidget(bestMatchLabel);
    mainLayout->addWidget(bestMatchInput);
    mainLayout->addWidget(bestMatchButton);
    mainLayout->addWidget(bestMatch);

    this->loadDocuments();
    this->setLayout(mainLayout);

    QObject::connect(this->lineEditForSearch, &QLineEdit::textChanged, this, &GUI::filterList);
    QObject::connect(this->bestMatchButton, &QPushButton::clicked, this, &GUI::findBestMatch);
    QObject::connect(this->bestMatchInput, &QLineEdit::returnPressed, this, &GUI::findBestMatch);
}

void GUI::loadDocuments()
{
    this->listWidgetWithDocuments->clear();
    for (auto document : this->service.getAllDocuments())
        this->listWidgetWithDocuments->addItem(QString::fromStdString(document.toString()));
}

void GUI::filterList()
{
    std::string searchAfter = this->lineEditForSearch->text().toStdString();
    if (searchAfter.empty())
    {
        this->loadDocuments();
        return;
    }
    this->listWidgetWithDocuments->clear();
    for (auto document : this->service.getDocumentsBySearch(searchAfter))
        this->listWidgetWithDocuments->addItem(QString::fromStdString(document.toString()));
}

void GUI::findBestMatch()
{
    std::string searchAfter = this->bestMatchInput->text().toStdString();
    this->bestMatch->setText(QString::fromStdString(this->service.findBestMatch(searchAfter)));
}