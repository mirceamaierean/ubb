//
// Created by Mircea Maierean on 14.06.2023.
//

#ifndef PRACTIC_SUBJECT_H
#define PRACTIC_SUBJECT_H

#include "observer.h"
#include <vector>
#include <memory>

using namespace std;

class Subject {
private:
    vector <unique_ptr<Observer> > observers;
public:
    void registerObserver(Observer *observer) { this->observers.emplace_back(observer); }
    void notify()
    {
        for (auto &obs : observers)
            obs->update();
    }
};


#endif //PRACTIC_SUBJECT_H
