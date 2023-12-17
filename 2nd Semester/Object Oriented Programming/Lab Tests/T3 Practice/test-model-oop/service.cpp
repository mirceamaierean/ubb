//
// Created by Mircea Maierean on 24.05.2023.
//

#include "service.h"

std::vector<Car> Service::getCarsByManufacturer(std::string manufacturerOfTheCar)
{
    // Based on this function, we'll get all the cars we need, and the number will be the size of the vector
    std::vector<Car> filteredCarsByManufacturer;
    for (auto car : this->repo.getAllCars())
        if (car.getManufacturer() == manufacturerOfTheCar)
            filteredCarsByManufacturer.push_back(car);
    return filteredCarsByManufacturer;
}

std::vector<Car> Service::getAllCars()
{
    std::vector<Car> cars = repo.getAllCars();
    std::sort(cars.begin(), cars.end());
    return cars;
}
