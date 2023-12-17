//
// Created by Mircea Maierean on 14.06.2023.
//

#ifndef PRACTIC_DEPARTMENT_H
#define PRACTIC_DEPARTMENT_H

#include <iostream>

using namespace std;

class Department {
private:
    string name, description;
public:
    Department(string name = "", string description = "") : name{name}, description{description} {};
    string getName() { return this->name; }
    string getDescription() { return this->description; }
};


#endif //PRACTIC_DEPARTMENT_H
