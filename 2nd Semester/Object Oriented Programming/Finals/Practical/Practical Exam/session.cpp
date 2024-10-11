//
// Created by Mircea Maierean on 14.06.2023.
//

#include "session.h"
#include <algorithm>

vector<string> Session::getVolunteersFromDepartment(string department) {
    vector<string> volunteers;
    for (auto vol : this->repository.getVolunteers())
        if (vol.getDepartmentName() == department)
            volunteers.push_back(vol.getVolunteer());
    sort(volunteers.begin(), volunteers.end());
    return volunteers;
}

vector<string> Session::getUnassigned() {
    vector<string> volunteers;
    for (auto vol : this->repository.getVolunteers())
        if (vol.getDepartmentName() == "Unassigned")
            volunteers.push_back(vol.getVolunteer());
    sort(volunteers.begin(), volunteers.end());
    return volunteers;
}

void Session::addVolunteer(string name, string email, string interests, string department) {
    this->repository.addVolunteer(name, email, interests, department);
    this->notify();
}

void Session::assignVolunteer(std::string key, std::string department) {
    istringstream iss(key);
    const char sep = '|';
    string name, email, interests;
    getline(iss, name, sep);
    getline(iss, email, sep);
    getline(iss, interests, sep);
    for (int i = 0; i < this->repository.getVolunteers().size(); i++)
        if (this->repository.getVolunteers()[i].getVolunteer() == key)
        {
            this->repository.assignVolunteer(i, department);
            this->notify();
            break;
        }
}

vector <pair <int, string>> Session::getStatistics() {
    map <string, int> stats;

    for (auto dep : this->repository.getDepartments())
        stats[dep.getName()] = this->getVolunteersFromDepartment(dep.getName()).size();

    int unassigneds = this->getUnassigned().size();
    if (unassigneds > 0)
        stats["Unassigned"] = unassigneds;
    vector <pair <int, string>> result;
    for (auto stat : stats)
        result.push_back(make_pair(stat.second, stat.first));
    sort(result.begin(), result.end());
    return result;
}

vector <string> Session::getMostSuitable(string description) {
    map <string, int> stats;

    for (auto vol : this->repository.getVolunteers())
    {
        if (vol.getDepartmentName() != "Unassigned")
            continue;
        istringstream iss(vol.getInterests());
        string interest;
        const char sep = ',';
        stats[vol.getName()] = 0;
        while (getline(iss, interest, sep))
        {
            if (description.find(interest) != string::npos) {
                stats[vol.getName()]++;
            }
        }

    }
    vector <pair <int, string>> result;

    for (auto stat : stats)
        result.push_back(make_pair(stat.second, stat.first));

    sort(result.begin(), result.end(), greater<pair<int, string>>());

    vector <string> bestThree;
    for (int i = 0; i < 3 && i < result.size(); i++)
        bestThree.push_back(result[i].second + " " + to_string(result[i].first));

    return bestThree;
}