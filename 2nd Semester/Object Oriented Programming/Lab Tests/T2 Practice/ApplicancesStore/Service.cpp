#include "Service.h"

void Service::addAppliance(Appliance *appliance)
{
  this->appliances.push_back(appliance);
}

void Service::generateRandomEntries()
{
  this->appliances.push_back(new Refrigerator("14", 2000, "A", true));
  this->appliances.push_back(new Refrigerator("25", 1699, "A+", false));
  this->appliances.push_back(new Refrigerator("34", 1200, "A++", true));
  this->appliances.push_back(new DishWasher("17", 300, 2.5, 700));
  this->appliances.push_back(new DishWasher("56", 100, 4.6, 50));
}

std::vector<Appliance *> Service::getAllApliances()
{
  return this->appliances;
}

std::vector<Appliance *> Service::getAllWithConsumedElectricityLessThan(double maximumElectricity)
{
  std::vector<Appliance *> appliancesWithConsumedElectricity;
  for (auto appliance : this->appliances)
    if (appliance->consumedElectricity() < maximumElectricity)
      appliancesWithConsumedElectricity.push_back(appliance);
  return appliancesWithConsumedElectricity;
}

std::vector<Appliance *> Service::getAllWithConsumedElectricityMoreThan(double minimumElectricity)
{
  std::vector<Appliance *> appliancesWithConsumedElectricity;
  for (auto appliance : this->appliances)
    if (appliance->consumedElectricity() > minimumElectricity)
      appliancesWithConsumedElectricity.push_back(appliance);
  std::sort(appliancesWithConsumedElectricity.begin(), appliancesWithConsumedElectricity.end(), comparisonFunction);
  return appliancesWithConsumedElectricity;
}

void Service::writeToFile(std::string fileName, double electricity)
{
  std::ofstream writeToFileStream(fileName);
  for (auto appliance : this->getAllWithConsumedElectricityMoreThan(electricity))
    writeToFileStream << appliance->toString() << "\n";
  writeToFileStream.close();
}
