#pragma once
#include "Car.h"
#include <vector>
#include <algorithm>
#include <fstream>

class Service
{
private:
  std::vector<Car> cars;

public:
  Service()
  {
    this->generateCars();
  };
  ~Service()
  {
    for (auto car : this->cars)
      car.destroyEngine();
  }
  static inline bool functionOfComparison(Car car1, Car car2);
  void generateCars();
  void addCar(std::string bodyStyle, std::string engineType, int autonomy = 0);
  double getPriceOfLastCarAdded();
  std::vector<Car> getAllCars();
  std::vector<Car> getCarsWithMaxPrice(double maxPrice);
  void writeToFile(std::string fileName, std::vector<Car> carsToWriteToFile);
};