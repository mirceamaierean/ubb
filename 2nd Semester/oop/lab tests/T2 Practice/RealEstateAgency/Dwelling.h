#pragma once
#include <iostream>

class Dwelling
{
private:
  double price;
  bool isProfitable;

public:
  Dwelling(double price = 0, bool isProfitable = false) : price{price}, isProfitable{isProfitable} {};
  ~Dwelling(){};
  double getPrice() { return this->price; };
  bool isDwellingProfitable() { return this->isProfitable; };
  std::string toString() { return "Price: " + std::to_string(this->price) + "\nIs Profitable?: " + std::to_string(this->isProfitable); };
};