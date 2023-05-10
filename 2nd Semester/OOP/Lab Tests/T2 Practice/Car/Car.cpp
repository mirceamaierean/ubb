#include "Car.h"

double Car::computePrice()
{
  double price = 8000 + this->engine->getPrice();
  if (this->bodyStyle == "Convertible")
    price += 1000;
  return price;
}

std::string Car::toString()
{
  return "Body Style: " + this->bodyStyle + "\n" + this->engine->toString() + "\nBase Price: " + std::to_string(this->computePrice()) + '\n';
}
