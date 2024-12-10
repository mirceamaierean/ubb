//
// Created by Mircea Maierean on 25.05.2023.
//

#ifndef BILLS_BILLS_H
#define BILLS_BILLS_H
#include <iostream>
using namespace std;

class Bill
{
private:
    string companyName, code;
    double sum;
    bool isPaid;
public:
    Bill(string companyName = "", string code = "", double sum = 0, bool isPaid = false) : companyName{companyName}, code{code}, sum{sum}, isPaid{isPaid} {};
    string getCompanyName() const { return this->companyName; };
    string getCode() const { return this->code; };
    string toString() const
    {
        string isPaidString = isPaid == true ? "true" : "false";
        return this->companyName + " " + this->code + " " + to_string(sum) + " " + isPaidString;
    }

    bool getIsPaid() const { return this->isPaid; };
    double getSum() const { return this->sum; };

    inline bool operator <(const Bill &other) const
    {
        return this->companyName < other.getCompanyName();
    }
};

#endif //BILLS_BILLS_H
