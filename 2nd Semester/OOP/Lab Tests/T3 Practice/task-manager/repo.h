//
// Created by Mircea Maierean on 24.05.2023.
//

#ifndef TASK_MANAGER_REPO_H
#define TASK_MANAGER_REPO_H
#include "task.h"
#include <vector>
#include <fstream>
#include <sstream>

class Repo{
private:
    std::vector <Task> tasks;
public:
    Repo() { this->populateRepo(); }
    void populateRepo();
    std::vector<Task> getAllTasks() { return this->tasks; }
};
#endif //TASK_MANAGER_REPO_H
