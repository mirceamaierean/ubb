//
// Created by Mircea Maierean on 14.06.2023.
//

#ifndef PRACTIC_OBSERVER_H
#define PRACTIC_OBSERVER_H

#include <iostream>

using namespace std;

class Observer
{
public:
    virtual void update() = 0;
};

#endif //PRACTIC_OBSERVER_H
