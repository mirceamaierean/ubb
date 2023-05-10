#include "RealEstateAgency.h"

void RealEstateAgency::addInitialEntries()
{
  this->dwellings.push_back(Dwelling(60000, true));
  this->clients.push_back(new Person("Ion", 700));
  this->clients.push_back(new Person("Ana", 600));
  this->clients.push_back(new Company("BCR", 33343, 293021));
  this->clients.push_back(new Company("BRD", 10, 20));
}

Dwelling RealEstateAgency::addDwelling(double price, bool isProfitable)
{
  Dwelling dwelling = Dwelling(price, isProfitable);
  dwellings.push_back(dwelling);
  return dwelling;
}

void RealEstateAgency::removeClient(std::string name)
{
  for (int index = 0; index < this->clients.size(); ++index)
    if (clients[index]->getName() == name)
    {
      clients.erase(clients.begin() + index);
      break;
    }
}

std::vector<Client *> RealEstateAgency::getInterstedClients(Dwelling dwelling)
{
  std::vector<Client *> interestedClients;
  for (auto client : this->clients)
    if (client->isInterested(dwelling))
      interestedClients.push_back(client);
  return interestedClients;
}

std::vector<Client *> RealEstateAgency::getClients()
{
  return this->clients;
}

std::vector<Dwelling> RealEstateAgency::getDwellings()
{
  return this->dwellings;
}

void RealEstateAgency::writeToFile(std::string fileName)
{
  std::ofstream writeToFile(fileName);
  for (auto client : this->clients)
    writeToFile << client->toString() << '\n';
}
