#pragma once
#include "Client.h"
#include <vector>
#include <fstream>

class RealEstateAgency
{
private:
  std::vector<Dwelling> dwellings;
  std::vector<Client *> clients;

public:
  RealEstateAgency()
  {
    this->addInitialEntries();
  };
  ~RealEstateAgency()
  {
    for (auto client : clients)
      delete client;
  };
  void addInitialEntries();
  Dwelling addDwelling(double price, bool isProfitable);
  void removeClient(std::string name);
  std::vector<Client *> getInterstedClients(Dwelling dwelling);
  std::vector<Client *> getClients();
  std::vector<Dwelling> getDwellings();
  void writeToFile(std::string fileName);
};