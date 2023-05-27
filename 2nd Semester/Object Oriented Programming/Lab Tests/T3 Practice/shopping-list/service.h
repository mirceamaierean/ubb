//
// Created by Mircea Maierean on 24.05.2023.
//

#ifndef SHOPPING_LIST_SERVICE_H
#define SHOPPING_LIST_SERVICE_H
#include "repository.h"
#include <algorithm>

class Service{
private:
    Repository repository;
public:
    static inline bool functionOfComparison(Item &item1, Item &item2) {return item1.getQuantity() < item2.getQuantity();};
    std::vector<Item> getAllItems();
    std::vector<Item> getItemsByCategory(std::string category);
    std::vector<Item> getItemsThatContainString(std::string search);
};

#endif //SHOPPING_LIST_SERVICE_H
