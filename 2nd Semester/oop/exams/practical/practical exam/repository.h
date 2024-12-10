//
// Created by Mircea Maierean on 14.06.2023.
//

#ifndef PRACTIC_REPOSITORY_H
#define PRACTIC_REPOSITORY_H

#include "volunteer.h"
#include "department.h"
#include <fstream>
#include <sstream>

class Repository{
private:
    string departmentsFilePath, volunteersFilePath;
    vector <Department> departments;
    vector <Volunteer> volunteers;
public:
    Repository()
    {
        this->departmentsFilePath = "/Users/mirceamaierean/practic/departments.txt";
        this->volunteersFilePath = "/Users/mirceamaierean/practic/volunteers.txt";
        this->loadRepo();
    }
    ~Repository();
    void loadRepo();
    void addVolunteer(string name, string email, string interests, string department);
    void assignVolunteer(int position, string department);
    vector <Department> &getDepartments() { return this->departments; }
    vector <Volunteer> &getVolunteers() { return this->volunteers; }
};


#endif //PRACTIC_REPOSITORY_H
