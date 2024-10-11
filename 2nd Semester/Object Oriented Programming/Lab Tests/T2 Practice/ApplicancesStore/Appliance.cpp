#include "Appliance.h"

std::string Appliance::toString()
{
  return "ID: " + this->id + "\nWeight: " + std::to_string(this->weight) + "\n";
}

double Refrigerator::consumedElectricity()
{
  double consumedElectricity = 30;
  if (this->electricityUsageClass == "A")
    consumedElectricity *= 3;
  else if (this->electricityUsageClass == "A+")
    consumedElectricity *= 2.5;
  else if (this->electricityUsageClass == "A++")
    consumedElectricity *= 2;
  if (this->hasFreezer)
    consumedElectricity += 20;
  return consumedElectricity;
}

std::string Refrigerator::toString()
{
  return Appliance::toString() + "Electricity Usage Class: " + this->electricityUsageClass + "\nHas Freezer: " + std::to_string(this->hasFreezer) + "\nConsumed Electricity: " + std::to_string(this->consumedElectricity()) + '\n';
}

double DishWasher::consumedElectricity()
{
  return 20 * this->washingCycleLength * this->consumedElectricityForOneHour;
}

std::string DishWasher::toString()
{
  return Appliance::toString() + "Washing Cycle Length: " + std::to_string(this->washingCycleLength) + "\nConsumed Electricity for One Hour: " + std::to_string(this->consumedElectricityForOneHour) + "\nConsumed Electricity: " + std::to_string(this->consumedElectricity()) + '\n';
}
