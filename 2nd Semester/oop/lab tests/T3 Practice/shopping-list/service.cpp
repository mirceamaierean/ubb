//
// Created by Mircea Maierean on 24.05.2023.
//

#include "service.h"

std::vector<Item> Service::getAllItems() {
    std::vector<Item> items = this->repository.getItems();
    std::sort(items.begin(), items.end());
    return items;
}

std::vector<Item> Service::getItemsByCategory(std::string category) {
    std::vector<Item> items = this->repository.getItems();
    std::vector<Item> filteredItems;
    for (auto item : items)
        if (item.getCategory() == category)
            filteredItems.push_back(item);
    std::sort(filteredItems.begin(), filteredItems.end(), Service::functionOfComparison);
    return filteredItems;
}

std::vector<Item> Service::getItemsThatContainString(std::string search) {
    std::vector<Item> items = this->repository.getItems();
    std::vector<Item> filteredItems;
    for (auto item : items)
        if (item.getCategory().find(search) != std::string::npos ||
        item.getName().find(search) != std::string::npos)
            filteredItems.push_back(item);
    return filteredItems;
}
