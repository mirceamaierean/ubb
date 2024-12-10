//
// Created by Mircea Maierean on 24.05.2023.
//

#include "repo.h"

void Repo::populateRepo()
{
    std::ifstream file("../tasks.txt");
    std::string line, description, estimatedDurationString, priorityString;
    int estimatedDuration, priority;
    const char sep = '|';
    while(std::getline(file, line))
    {
        std::istringstream iss(line);
        std::getline(iss, description, sep);
        std::getline(iss, estimatedDurationString, sep);
        estimatedDuration = std::stoi(estimatedDurationString);
        std::getline(iss, priorityString, sep);
        priority = std::stoi(priorityString);
        this->tasks.push_back(Task(description, estimatedDuration, priority));
        std::cout << this->tasks.back().toString() << '\n';
    }
}
