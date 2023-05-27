//
// Created by Mircea Maierean on 25.05.2023.
//

#ifndef BILLS_REPOSITORY_H
#define BILLS_REPOSITORY_H
#include "bills.h"
#include <vector>
#include <fstream>
#include <sstream>

class Repository
{
private:
    vector <Bill> bills;
public:
    Repository() { this->loadRepo(); };
    void loadRepo();
    vector <Bill> getAllBills() { return this->bills; };
};
#endif //BILLS_REPOSITORY_H
