//
// Created by Mircea Maierean on 24.05.2023.
//

#ifndef TEST_MODEL_OOP_SERVICE_H
#define TEST_MODEL_OOP_SERVICE_H
#include "repo.h"

class Service
{
private:
    Repository repo;
public:
    std::vector<Car> getAllCars();
    std::vector<Car> getCarsByManufacturer(std::string manufacturer);
};
#endif //TEST_MODEL_OOP_SERVICE_H
