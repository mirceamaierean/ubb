#pragma once
#include <vector>
#include <iostream>

class Sensor
{
protected:
  std::string producer;
  std::vector<double> recordings;

public:
  Sensor(std::string producer) : producer{producer} {};
  virtual ~Sensor(){};
  void addRecording(double recording);
  virtual bool sendAlert() { return true; };
  virtual double getPrice() { return 0; };
  virtual std::string toString();
  std::string getProducer();
};

class TemperatureSensor : public Sensor
{
private:
  double diamater;
  double length;

public:
  TemperatureSensor(std::string producer, double diamater, double length) : Sensor(producer), diamater{diamater}, length{length} {};
  bool sendAlert();
  double getPrice();
  std::string toString();
};

class HumiditySensor : public Sensor
{
public:
  HumiditySensor(std::string producer) : Sensor(producer){};
  bool sendAlert();
  double getPrice();
  std::string toString();
};

class SmokeSensor : public Sensor
{
public:
  SmokeSensor(std::string producer) : Sensor(producer){};
  bool sendAlert();
  double getPrice();
  std::string toString();
};