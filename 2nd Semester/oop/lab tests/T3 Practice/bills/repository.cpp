//
// Created by Mircea Maierean on 25.05.2023.
//

#include "repository.h"

void Repository::loadRepo()
{
    ifstream file("../bills.txt");
    std::string line, companyName, code, sumString, isPaidString;
    double sum;
    bool isPaid;
    const char delimiter = '|';
    while (getline(file, line))
    {
        istringstream iss(line);
        getline(iss, companyName, delimiter);
        getline(iss, code, delimiter);
        getline(iss, sumString, delimiter);
        getline(iss, isPaidString, delimiter);
        sum = stod(sumString);
        isPaid = isPaidString == "false" ? false : true;
        this->bills.push_back(Bill(companyName, code, sum, isPaid));
        cout << this->bills.back().toString() << '\n';
    }
}
