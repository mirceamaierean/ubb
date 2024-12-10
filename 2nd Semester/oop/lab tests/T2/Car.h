#pragma once
#include "Engine.h"

class Car
{
private:
  std::string bodyStyle;
  Engine *engine;

public:
  Car(std::string bodyStyle = "", Engine *engine = nullptr) : bodyStyle{bodyStyle}, engine{engine} {};
  ~Car(){};
  double computePrice();
  void destroyEngine();
  std::string toString();
};