//
// Created by Mircea Maierean on 24.05.2023.
//

#include "repository.h"

void Repository::loadFilesIntoRepo()
{
    std::ifstream file("../items.txt");
    std::string line;
    const char delimiter = '|';
    std::string category, name, quantityString;
    int quantity;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::getline(iss, category, delimiter);
        std::getline(iss, name, delimiter);
        std::getline(iss, quantityString, delimiter);
        quantity = std::stoi(quantityString);
        this->items.push_back(Item(category, name, quantity));
    }
}

std::vector<Item> Repository::getItems() {
    return this->items;
}
