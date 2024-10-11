#pragma once
#include <iostream>
#include "Device.h"

class UI
{
private:
  Device device;

public:
  UI(){};
  ~UI(){};
  void addSensor();
  void showAllSensors();
  void showAllSensorsThatEmitAllerts();
  void printAllSensorsWithPriceSmallerToFile();
  void runApp();
};