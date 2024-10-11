//
// Created by Mircea Maierean on 24.05.2023.
//

#ifndef SHOPPING_LIST_REPOSITORY_H
#define SHOPPING_LIST_REPOSITORY_H
#include "item.h"
#include <vector>
#include <sstream>
#include <fstream>

class Repository
{
private:
    std::vector<Item> items;
public:
    Repository() {this->loadFilesIntoRepo();};
    void loadFilesIntoRepo();
    std::vector<Item> getItems();
};

#endif //SHOPPING_LIST_REPOSITORY_H
