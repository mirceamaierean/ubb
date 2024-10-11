//
// Created by Mircea Maierean on 13.06.2023.
//

#ifndef PROGREMR_PERSON_H
#define PROGREMR_PERSON_H

#include <iostream>

class Person {
private:
    std::string name, role;
public:
    Person(std::string name = "", std::string role = "") : name{name}, role{role} {};
    std::string getName() const
    {
        return this->name;
    }
    std::string getRole() const
    {
        return this->role;
    }
};


#endif //PROGREMR_PERSON_H
