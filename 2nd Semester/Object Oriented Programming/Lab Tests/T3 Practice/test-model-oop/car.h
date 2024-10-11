//
// Created by Mircea Maierean on 24.05.2023.
//

#ifndef TEST_MODEL_OOP_CAR_H
#define TEST_MODEL_OOP_CAR_H
#include <iostream>

class Car
{
private:
    std::string manufacturer, model, colour;
    int year;
public:
    Car(std::string manufacturer, std::string model, int year, std::string colour) : manufacturer(manufacturer), model(model), year(year), colour(colour) {};
    std::string getManufacturer() const { return manufacturer; };
    std::string getModel() const { return model; };
    std::string getColour() const { return colour; };
    std::string toString() const { return manufacturer + " " + model + " " + std::to_string(year) + " " + colour; };
    int getYear() const { return year; };
    inline bool operator < (const Car& car) const { return this->manufacturer < car.getManufacturer(); };
};

#endif //TEST_MODEL_OOP_CAR_H
