//
// Created by Mircea Maierean on 13.06.2023.
//

#ifndef PROGREMR_OBSERVER_H
#define PROGREMR_OBSERVER_H


class Observer {
public:
    Observer() = default;;
    virtual ~Observer()= default;;
    virtual void update() const = 0;
};


#endif //PROGREMR_OBSERVER_H
