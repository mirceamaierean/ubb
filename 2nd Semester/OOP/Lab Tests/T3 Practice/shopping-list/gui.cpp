//
// Created by Mircea Maierean on 24.05.2023.
//

#include "gui.h"

GUI::GUI(QWidget *parent) : QWidget(parent)
{
    this->service = Service();
    QVBoxLayout *mainLayout = new QVBoxLayout();
    this->listWidgetAllItems = new QListWidget();
    this->listWidgetFilteredItems = new QListWidget();
    this->searchByCategoryLineEdit = new QLineEdit();
    this->searchByCategoryOrName = new QLineEdit();
    this->searchByCategoryButton = new QPushButton("Search by category");
    this->labelForSearchByCategory = new QLabel("Display by category");
    this->labelForSearchByCategoryOrName = new QLabel("Filter the initial list");
    mainLayout->addWidget(this->listWidgetAllItems);
    mainLayout->addWidget(this->labelForSearchByCategoryOrName);
    mainLayout->addWidget(this->searchByCategoryOrName);
    mainLayout->addWidget(this->labelForSearchByCategory);
    mainLayout->addWidget(this->searchByCategoryLineEdit);
    mainLayout->addWidget(this->searchByCategoryButton);
    mainLayout->addWidget(this->listWidgetFilteredItems);
    this->setLayout(mainLayout);
    this->populateListWidgetAllItems();
    QObject::connect(this->searchByCategoryOrName, &QLineEdit::textChanged, this, &GUI::populateListWidgetBasedOnSearch);
    QObject::connect(this->searchByCategoryButton, &QPushButton::clicked, this, &GUI::filterByCategory);
    QObject::connect(this->searchByCategoryLineEdit, &QLineEdit::returnPressed, this, &GUI::filterByCategory);
    QObject::connect(this->listWidgetAllItems, &QListWidget::itemSelectionChanged, this, &GUI::printSelectedItem);
}

void GUI::populateListWidgetAllItems()
{
    this->listWidgetAllItems->clear();
    std::vector<Item> allItems = this->service.getAllItems();
    for (auto item : allItems)
        this->listWidgetAllItems->addItem(QString::fromStdString(item.toString()));
}

void GUI::populateListWidgetBasedOnSearch()
{
    std::string categoryOrName = this->searchByCategoryOrName->text().toStdString();
    if (categoryOrName == "")
    {
        this->populateListWidgetAllItems();
        return;
    }
    this->listWidgetAllItems->clear();
    std::vector<Item> itemsFiltered = this->service.getItemsThatContainString(categoryOrName);
    for (auto item : itemsFiltered)
        this->listWidgetAllItems->addItem(QString::fromStdString(item.toString()));
}

void GUI::filterByCategory() {
    this->listWidgetFilteredItems->clear();
    std::string category = this->searchByCategoryLineEdit->text().toStdString();
    std::vector<Item> itemsFiltered = this->service.getItemsByCategory(category);
    for (auto item : itemsFiltered)
        this->listWidgetFilteredItems->addItem(QString::fromStdString(item.toString()));
}

void GUI::printSelectedItem() {
    QListWidgetItem *selectedItem = this->listWidgetAllItems->currentItem();
    if (selectedItem == nullptr)
        return;
    std::string itemAsString = selectedItem->text().toStdString();
    this->searchByCategoryLineEdit->setText(QString::fromStdString(itemAsString));
}