#pragma once
#include "Service.h"

class UI
{
private:
  Service service;

public:
  UI(){};
  ~UI(){};
  void addCar();
  void showAllCars();
  void writeCarsWithSmallerPriceToFile();
  void runApp();
};