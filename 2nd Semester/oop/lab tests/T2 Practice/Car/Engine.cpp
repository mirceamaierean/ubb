#include "Engine.h"

std::string Engine::toString()
{
  return "";
}

double ElectricEngine::getPrice()
{
  return this->basePrice + double(this->autonomy) * 0.01;
}

std::string ElectricEngine::toString()
{
  return "Type: Electric\nFuel Type: Electric\nAutonomy: " + std::to_string(this->autonomy) + "\nEngine Price: " + std::to_string(this->getPrice());
}

double TurboEngine::getPrice()
{
  if (this->fuelType == "Diesel")
    return this->basePrice + 1.5;
  return this->basePrice + 1;
}

std::string TurboEngine::toString()
{
  return "Engine Type: Turbo\nFuel Type: " + this->fuelType + "\nEngine Price: " + std::to_string(this->getPrice());
}