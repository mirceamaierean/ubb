#pragma once
#include <iostream>

class Engine
{
protected:
  double basePrice;

public:
  Engine(double basePrice = 3000) : basePrice{basePrice} {};
  virtual ~Engine(){};
  virtual double getPrice() { return basePrice; };
  virtual std::string toString();
};

class ElectricEngine : public Engine
{
private:
  int autonomy;

public:
  ElectricEngine(int autonomy = 0) : Engine{}, autonomy{autonomy} {};
  double getPrice();
  std::string toString();
};

class TurboEngine : public Engine
{
public:
  TurboEngine() : Engine{} {};
  double getPrice();
  std::string toString();
};