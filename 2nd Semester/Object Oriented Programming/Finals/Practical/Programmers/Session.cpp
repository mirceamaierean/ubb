//
// Created by Mircea Maierean on 13.06.2023.
//

#include "Session.h"
#include <fstream>
#include <sstream>
#include <algorithm>

void Session::loadRepo()
{
    std::ifstream file(this->personsFilePath);
    std::string name, role, row;
    const char sep = '|';
    while (std::getline(file, row))
    {
        std::istringstream iss(row);
        std::getline(iss, name, sep);
        std::getline(iss, role, sep);
        this->persons.emplace_back(name, role);
    }
    file.close();
    file = std::ifstream(this->issuesFilePath);
    std::string description, isOpen, nameReporter, nameSolver;
    while (std::getline(file, row))
    {
        std::istringstream iss(row);
        std::getline(iss, description, sep);
        std::getline(iss, isOpen, sep);
        std::getline(iss, nameReporter, sep);
        std::getline(iss, nameSolver, sep);
        this->issues.emplace_back(description, isOpen == "open", nameReporter, nameSolver);
    }
    std::sort(this->issues.begin(), this->issues.end());
    file.close();
}

Session &Session::operator=(const Session &other) {
    this->persons = other.persons;
    this->issues = other.issues;
    this->personsFilePath = other.personsFilePath;
    this->issuesFilePath = other.issuesFilePath;
    return *this;
}

void Session::removeIssue(int position) {
    this->issues.erase(this->issues.begin() + position);
    this->notify();
}

bool Session::checkIfIssueExists(const std::string &description) {
    for (const auto &issue : this->issues)
        if (issue.getDescription() == description)
            return true;
    return false;
}

void Session::addIssue(const std::string &description, bool isOpen, const std::string &nameReporter,
                       const std::string &nameSolver) {
    if (this->checkIfIssueExists(description))
        throw std::runtime_error("Issue already exists!");
    if (description.empty())
        throw std::runtime_error("Description cannot be empty!");
    this->issues.emplace_back(description, isOpen, nameReporter, nameSolver);
    this->notify();
}

void Session::resolveIssue(int position, const std::string &nameSolver) {
    this->issues[position].setIsOpen(false);
    this->issues[position].setSolver(nameSolver);
    this->notify();
}

void Session::saveIssues() {
    std::ofstream file(this->issuesFilePath);
        for (const auto &issue : this->issues)
            file << issue.formatAsString() << "\n";
        file.close();
}