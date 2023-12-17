#pragma once
#include "RealEstateAgency.h"

class UI
{
private:
  RealEstateAgency realEstateAgency;

public:
  UI(){};
  ~UI(){};
  void removeAClient();
  void showAllClientsAndDwellings();
  void addDwelling();
  void saveClientsToFile();
  void runApp();
};