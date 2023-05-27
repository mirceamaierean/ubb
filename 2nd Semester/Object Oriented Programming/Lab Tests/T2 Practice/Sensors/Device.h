#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Sensor.h"

class Device
{
private:
  std::vector<Sensor *> sensors;
  bool hasWifi;

public:
  Device() : hasWifi{true}
  {
    Sensor *tm = new TemperatureSensor("Prod1", 10, 20);
    tm->addRecording(20);
    tm->addRecording(30);
    tm->addRecording(40);
    sensors.push_back(tm);

    Sensor *hm = new HumiditySensor("Prod2");
    hm->addRecording(50);
    hm->addRecording(60);
    hm->addRecording(70);
    sensors.push_back(hm);

    Sensor *sm = new SmokeSensor("Prod3");
    sm->addRecording(80);
    sm->addRecording(90);
    sm->addRecording(100);
    sensors.push_back(sm);
  };
  Device(bool hasWifi) : hasWifi{hasWifi} {};
  ~Device()
  {
    for (auto sensor : sensors)
      delete sensor;
  };
  static inline bool compareSensors(Sensor *sensor1, Sensor *sensor2);
  void addSensor(Sensor *sensor);
  std::vector<Sensor *> getAllSensors();
  std::vector<Sensor *> getAlertingSensors();
  std::vector<Sensor *> getSensorsWithPriceSmallerThanValue(double price);
  void writeToFile(std::string nameOfFile, double price);
};