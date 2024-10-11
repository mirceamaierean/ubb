//
// Created by Mircea Maierean on 25.05.2023.
//

#include "service.h"

vector<Bill> Service::getAllBillsSorted() {
    vector<Bill> bills = this->getAllBills();
    sort(bills.begin(), bills.end());
    return bills;
}

double Service::calculateAmountOfBillsFromCompany(std::string company) {
    double total = 0;
    for (auto bill: this->repository.getAllBills())
        if (bill.getCompanyName() == company && !bill.getIsPaid())
            total += bill.getSum();
    return total;
}