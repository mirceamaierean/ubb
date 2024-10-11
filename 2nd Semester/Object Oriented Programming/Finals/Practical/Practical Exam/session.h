//
// Created by Mircea Maierean on 14.06.2023.
//

#ifndef PRACTIC_SESSION_H
#define PRACTIC_SESSION_H

#include "subject.h"
#include "repository.h"
#include <map>

class Session : public Subject{
private:
    Repository &repository;
public:
    Session(Repository &repository) : repository{repository} {};
    vector<string> getVolunteersFromDepartment(string department);
    vector<string> getUnassigned();
    vector <pair <int, string>> getStatistics();
    vector <string> getMostSuitable(string description);
    void addVolunteer(string name, string email, string interests, string department);
    void assignVolunteer(string key, string department);
};


#endif //PRACTIC_SESSION_H
