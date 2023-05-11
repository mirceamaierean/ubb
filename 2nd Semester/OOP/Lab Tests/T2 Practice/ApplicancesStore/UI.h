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
  void addAppliance();
  void showAllApliances();
  void showAllEfficientAppliances();
  void writeToFile();
};