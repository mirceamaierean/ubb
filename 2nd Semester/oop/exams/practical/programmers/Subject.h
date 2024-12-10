//
// Created by Mircea Maierean on 13.06.2023.
//

#ifndef PROGREMR_SUBJECT_H
#define PROGREMR_SUBJECT_H

#include "Observer.h"
#include <vector>

class Subject {
private:
    std::vector <std::unique_ptr<Observer> > observers;
public:
    Subject() = default;
    ~Subject() = default;
    void registerObserver(Observer *observer) { this->observers.emplace_back(observer); };
    void notify() { for (auto &observer : this->observers) observer->update(); };
};

#endif //PROGREMR_SUBJECT_H
