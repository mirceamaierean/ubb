//
// Created by Mircea Maierean on 13.06.2023.
//

#ifndef PROGREMR_SESSION_H
#define PROGREMR_SESSION_H

#include "Subject.h"
#include "Person.h"
#include "Issue.h"
class Session : public Subject{
private:
    std::vector <Person> persons;
    std::vector <Issue> issues;
    std::string personsFilePath, issuesFilePath;
public:
    Session()
    {
        this->personsFilePath = "/Users/mirceamaierean/progremr/persons.txt";
        this->issuesFilePath = "/Users/mirceamaierean/progremr/issues.txt";
        this->loadRepo();
    }
    Session &operator=(const Session &other);
    ~Session() { this->saveIssues(); };
    std::vector <Person> &getPersons() { return this->persons; };
    std::vector <Issue> &getIssues() { return this->issues; };
    void loadRepo();
    void saveIssues();
    bool checkIfIssueExists(const std::string &description);
    void addIssue(const std::string &description, bool isOpen, const std::string &nameReporter, const std::string &nameSolver);
    void removeIssue(int position);
    void resolveIssue(int position, const std::string &nameSolver);
};


#endif //PROGREMR_SESSION_H
