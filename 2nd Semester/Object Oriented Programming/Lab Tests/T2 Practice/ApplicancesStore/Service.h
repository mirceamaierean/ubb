#pragma once
#include "Appliance.h"
#include <vector>
#include <algorithm>
#include <fstream>

class Service
{
private:
  std::vector<Appliance *> appliances;

public:
  Service() { this->generateRandomEntries(); };
  ~Service()
  {
    for (auto appliance : this->appliances)
      delete appliance;
  };
  static inline bool comparisonFunction(Appliance *appliance1, Appliance *appliance2) { return appliance1->getId() < appliance2->getId(); };
  void addAppliance(Appliance *appliance);
  void generateRandomEntries();
  std::vector<Appliance *> getAllApliances();
  std::vector<Appliance *> getAllWithConsumedElectricityLessThan(double maximumElectricity);
  std::vector<Appliance *> getAllWithConsumedElectricityMoreThan(double minimumElectricity);
  void writeToFile(std::string fileName, double electricity);
};