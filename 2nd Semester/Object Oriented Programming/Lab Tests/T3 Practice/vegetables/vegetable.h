//
// Created by Mircea Maierean on 24.05.2023.
//

#ifndef VEGETABLES_VEGETABLE_H
#define VEGETABLES_VEGETABLE_H
#include <iostream>

using namespace std;

class Vegetable
{
private:
    string family, name, parts;
public:
    Vegetable(string family = "", string name = "", string parts = "") : family{family}, name{name}, parts{parts}{};
    string getFamily() const { return this->family; }
    string getName() const { return this->name; }
    string getParts() const { return this->parts; }
    inline bool operator < (const Vegetable &other) const
    {
        return this->name < other.getName();
    }
};

#endif //VEGETABLES_VEGETABLE_H
