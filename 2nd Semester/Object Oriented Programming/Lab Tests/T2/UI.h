#pragma once
#include "Service.h"

class UI
{
private:
  Service service;

public:
  UI(){};
  ~UI(){};
  void runApp();
  void showAllCars();
  void addCar();
  void writeCarsToFile();
};
