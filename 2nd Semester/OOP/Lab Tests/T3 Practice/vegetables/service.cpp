//
// Created by Mircea Maierean on 24.05.2023.
//

#include "service.h"

set<string> Service::getFamilies() {
    set<string> familiesOfVegetables;
    for (auto vegetable : this->repository.getAllVegetables())
        familiesOfVegetables.insert(vegetable.getFamily());
    return familiesOfVegetables;
}

vector<Vegetable> Service::getAllVegetablesBelongingToFamily(std::string familyOfVegetables) {
    vector <Vegetable> vegetablesBelongingToFamily;
    for (auto vegetable : this->repository.getAllVegetables())
        if (vegetable.getFamily() == familyOfVegetables)
            vegetablesBelongingToFamily.push_back(vegetable);
    return vegetablesBelongingToFamily;
}

Vegetable Service::getVegetableFromName(std::string name) {
    for (auto vegetable : this->repository.getAllVegetables())
        if (vegetable.getName() == name)
            return vegetable;
    return Vegetable();
}