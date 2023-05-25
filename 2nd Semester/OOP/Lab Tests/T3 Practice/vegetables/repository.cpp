//
// Created by Mircea Maierean on 24.05.2023.
//

#include "repository.h"

void Repository::loadRepo()
{
    ifstream file("../vegetables.txt");
    string line, family, name, part;
    const char del = '|';
    while (getline(file, line))
    {
        istringstream iss(line);
        getline(iss, family, del);
        getline(iss, name, del);
        getline(iss, part, del);

        this->vegetables.push_back(Vegetable(family, name, part));
    }
}
