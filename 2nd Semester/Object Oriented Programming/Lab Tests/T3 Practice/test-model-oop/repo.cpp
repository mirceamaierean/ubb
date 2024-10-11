//
// Created by Mircea Maierean on 24.05.2023.
//

#include "repo.h"

void Repository::loadFromFile()
{
    std::ifstream file("../cars.txt");
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string manufacturer, model, colour, yearString;
        int year;
        const char delimiter = '|';
        std::getline(iss, manufacturer, delimiter);
        std::getline(iss, model, delimiter);
        std::getline(iss, yearString, delimiter);
        year = std::stoi(yearString);
        std::getline(iss, colour, delimiter);
        cars.push_back(Car(manufacturer, model, year, colour));
    }
    file.close();
}