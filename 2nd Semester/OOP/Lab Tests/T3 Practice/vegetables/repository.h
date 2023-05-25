//
// Created by Mircea Maierean on 24.05.2023.
//

#ifndef VEGETABLES_REPOSITORY_H
#define VEGETABLES_REPOSITORY_H
#include "vegetable.h"
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Repository{
private:
    vector<Vegetable> vegetables;
public:
    Repository() { this->loadRepo(); };
    void loadRepo();
    vector <Vegetable> getAllVegetables() { return this->vegetables; }
};

#endif //VEGETABLES_REPOSITORY_H
