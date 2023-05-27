#pragma once
#include <iostream>

class Appliance
{
protected:
  std::string id;
  double weight;

public:
  Appliance(std::string id = "", double weight = 0) : id{id}, weight{weight} {};
  virtual ~Appliance(){};
  std::string getId() { return this->id; };
  virtual double consumedElectricity() { return 0; };
  virtual std::string toString();
};

class Refrigerator : public Appliance
{
private:
  std::string electricityUsageClass;
  bool hasFreezer;

public:
  Refrigerator(std::string id = "", double weight = 0, std::string electricityUsageClass = "", bool hasFreezer = false) : Appliance{id, weight}, electricityUsageClass{electricityUsageClass}, hasFreezer{hasFreezer} {};
  double consumedElectricity();
  std::string toString();
};

class DishWasher : public Appliance
{
private:
  double washingCycleLength, consumedElectricityForOneHour;

public:
  DishWasher(std::string id = "", double weight = 0, double washingCycleLength = 0, double consumedElectricityForOneHour = 0) : Appliance{id, weight}, washingCycleLength{washingCycleLength}, consumedElectricityForOneHour{consumedElectricityForOneHour} {};
  double consumedElectricity();
  std::string toString();
};