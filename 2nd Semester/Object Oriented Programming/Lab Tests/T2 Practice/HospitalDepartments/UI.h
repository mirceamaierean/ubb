#pragma once
#include "Controller.h"

class UI
{
private:
  Controller applicationController;

public:
  UI(){};
  ~UI(){};
  void runApp();
  void addDepartment();
  void showAllDepartments();
  void showAllEfficientDeparments();
  void writeToFile();
};