//
// Created by Mircea Maierean on 24.05.2023.
//

#include "service.h"


std::vector<Task> Service::getAllTasks()
{
    std::vector<Task> tasks = this->repo.getAllTasks();
    std::sort(tasks.begin(), tasks.end());
    return tasks;
}

std::vector<Task> Service::getTasksWithGivenPriority(int priority) {
    std::vector <Task> tasksWithGivenPriority;
    for (auto task : this->repo.getAllTasks())
        if (task.getPriority() == priority)
            tasksWithGivenPriority.push_back(task);
    return tasksWithGivenPriority;
}
