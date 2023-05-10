#include "Service.h"

Engine *Service::createEngine(std::string engineType, std::string fuelType, int autonomy)
{
  Engine *engine = nullptr;
  if (engineType == "Electric")
    engine = new ElectricEngine(fuelType, autonomy);
  else if (engineType == "Turbo")
    engine = new TurboEngine(fuelType);
  return engine;
}

Car Service::getLastAddedCar()
{
  return this->cars.back();
}

void Service::generateEntries()
{
  this->cars.push_back(Car("Sedan", this->createEngine("Electric", "Electric", 6000)));
  this->cars.push_back(Car("Convertible", this->createEngine("Electric", "Electric", 15000)));
  this->cars.push_back(Car("Sedan", this->createEngine("Turbo", "Gasoline")));
  this->cars.push_back(Car("Sedan", this->createEngine("Turbo", "Diesel")));
  this->cars.push_back(Car("Convertible", this->createEngine("Turbo", "Gasoline")));
  this->cars.push_back(Car("Convertible", this->createEngine("Turbo", "Diesel")));
}

inline bool Service::comparisonFunction(Car car1, Car car2)
{
  return car1.computePrice() < car2.computePrice();
}

void Service::addCar(std::string bodyStyle, std::string engineType, std::string fuelType, int autonomy)
{
  Engine *engine = this->createEngine(engineType, fuelType, autonomy);
  this->cars.push_back(Car(bodyStyle, engine));
}

std::vector<Car> Service::getCarsWithMaximumPrice(double maxPrice)
{
  std::vector<Car> carsWithSmallerPrice;
  for (auto car : this->cars)
    if (car.computePrice() < maxPrice)
      carsWithSmallerPrice.push_back(car);
  std::sort(carsWithSmallerPrice.begin(), carsWithSmallerPrice.end(), comparisonFunction);
  return carsWithSmallerPrice;
}

std::vector<Car> Service::getAllCars()
{
  return this->cars;
}

void Service::writeToFile(std::string fileName, std::vector<Car> cars)
{
  std::ofstream writeToFile(fileName);
  for (auto car : cars)
    writeToFile << car.toString() << '\n';
}
