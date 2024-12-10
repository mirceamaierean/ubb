#include "Client.h"

std::string Client::toString()
{
  return "Name: " + this->name + "\nIncome: " + std::to_string(this->income) + "\n";
}

bool Person::isInterested(Dwelling dwelling)
{
  return dwelling.getPrice() / 1000.00 <= this->totalIncome();
}

std::string Person::toString()
{
  return "Type: Person\n" + Client::toString() + "Total Income: " + std::to_string(this->totalIncome()) + '\n';
}

double Company::totalIncome()
{
  return this->income + this->moneyFromInvestments;
}

std::string Company::toString()
{
  return "Type: Company\n" + Client::toString() + "Money from investments: " + std::to_string(moneyFromInvestments) + "\nTotal Income: " + std::to_string(this->totalIncome()) + '\n';
}

bool Company::isInterested(Dwelling dwelling)
{
  return dwelling.getPrice() / 100.00 <= this->totalIncome() && dwelling.isDwellingProfitable();
}
