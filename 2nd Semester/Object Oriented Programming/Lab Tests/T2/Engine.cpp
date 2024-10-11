#include "Engine.h"

std::string Engine::toString()
{
  return "Base price: " + std::to_string(this->basePrice) + "\n";
}

double ElectricEngine::getPrice()
{
  return Engine::getPrice() + double(this->autonomy) * 0.01;
}

std::string ElectricEngine::toString()
{
  return "Type of engine: Electric\nAutonomy: " + std::to_string(this->autonomy) + "\nEngine Price: " + std::to_string(this->getPrice()) + "\n";
}

double TurboEngine::getPrice()
{
  return Engine::getPrice() + 100;
}

std::string TurboEngine::toString()
{
  return "Type of engine: Turbo\nEngine Price: " + std::to_string(this->getPrice()) + "\n";
}
