//
// Created by Mircea Maierean on 25.05.2023.
//

#ifndef BILLS_SERVICE_H
#define BILLS_SERVICE_H
#include "repository.h"
#include <algorithm>

class Service
{
private:
    Repository repository;
public:
    vector <Bill> getAllBills() { return this->repository.getAllBills(); } ;
    vector <Bill> getAllBillsSorted();
    double calculateAmountOfBillsFromCompany(string company);
};

#endif //BILLS_SERVICE_H
