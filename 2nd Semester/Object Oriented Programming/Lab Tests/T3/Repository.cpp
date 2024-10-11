//
// Created by Mircea Maierean on 25.05.2023.
//

#include "Repository.h"

void Repository::loadRepo() {
    std::ifstream file("../documents.txt");
    std::string line, name, listOfKeywords, content;
    const char delimiter = '|';
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::getline(iss, name, delimiter);
        std::getline(iss, listOfKeywords, delimiter);
        std::getline(iss, content, delimiter);
        this->documents.emplace_back(name, listOfKeywords, content);
    }
}