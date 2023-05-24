//
// Created by Mircea Maierean on 24.05.2023.
//

#ifndef TEST_MODEL_OOP_REPO_H
#define TEST_MODEL_OOP_REPO_H
#include "car.h"
#include <fstream>
#include <vector>
#include <sstream>

class Repository
{
private:
    std::vector<Car> cars;
public:
    void loadFromFile();
    Repository(){this->loadFromFile();};
    std::vector<Car> getAllCars() {return cars; }
};
#endif //TEST_MODEL_OOP_REPO_H
