//
// Created by Mircea Maierean on 24.05.2023.
//

#ifndef VEGETABLES_SERVICE_H
#define VEGETABLES_SERVICE_H
#include "repository.h"
#include <algorithm>
#include <set>

using namespace std;

class Service
{
private:
    Repository repository;
public:
    set<string> getFamilies();
    vector<Vegetable> getAllVegetablesBelongingToFamily(string family);
    Vegetable getVegetableFromName(string name);
};
#endif //VEGETABLES_SERVICE_H
