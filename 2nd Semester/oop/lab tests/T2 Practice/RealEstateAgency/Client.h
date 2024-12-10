#pragma once
#include <iostream>
#include "Dwelling.h"

class Client
{
protected:
  std::string name;
  double income;

public:
  Client(std::string name = "", double income = 0) : name{name}, income{income} {};
  virtual ~Client(){};
  virtual double totalIncome() { return this->income; };
  virtual std::string toString();
  virtual bool isInterested(Dwelling dwelling) { return false; };
  std::string getName() { return this->name; };
};

class Person : public Client
{
public:
  Person(std::string name = "", double income = 0) : Client{name, income} {};
  bool isInterested(Dwelling dwelling);
  std::string toString();
};

class Company : public Client
{
private:
  double moneyFromInvestments;

public:
  Company(std::string name = "", double income = 0, double moneyFromInvestments = 0) : Client{name, income}, moneyFromInvestments{moneyFromInvestments} {};
  double totalIncome();
  std::string toString();
  bool isInterested(Dwelling dwelling);
};