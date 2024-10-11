//
// Created by Mircea Maierean on 24.05.2023.
//

#ifndef TASK_MANAGER_TASK_H
#define TASK_MANAGER_TASK_H
#include <iostream>

class Task
{
private:
    std::string description;
    int estimateDuration, priority;
public:
    Task(std::string description, int estimatedDuration, int priority) : description{description}, estimateDuration{estimatedDuration}, priority{priority} {};
    std::string toString() {
        return this->description + " " + std::to_string(estimateDuration) + " " + std::to_string(priority);
    }
    int getPriority() const { return this->priority; }
    int getEstimatedDuration() const { return this->estimateDuration; };
    inline bool operator < (const Task &other) const
    {
        return this->priority < other.getPriority();
    }
};

#endif //TASK_MANAGER_TASK_H
