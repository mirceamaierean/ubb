//
// Created by Mircea Maierean on 24.05.2023.
//

#ifndef TASK_MANAGER_SERVICE_H
#define TASK_MANAGER_SERVICE_H

#include "repo.h"
#include <algorithm>

class Service{
private:
    Repo repo;
public:
    std::vector <Task> getAllTasks();
    std::vector <Task> getTasksWithGivenPriority(int priority);
};

#endif //TASK_MANAGER_SERVICE_H
