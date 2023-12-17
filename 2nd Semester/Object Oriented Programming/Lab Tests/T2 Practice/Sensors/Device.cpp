#include "Device.h"

inline bool Device::compareSensors(Sensor *sensor1, Sensor *sensor2)
{
  return sensor1->getProducer() < sensor2->getProducer();
}

void Device::addSensor(Sensor *sensor)
{
  this->sensors.push_back(sensor);
}

std::vector<Sensor *> Device::getAllSensors()
{
  return this->sensors;
}

std::vector<Sensor *> Device::getAlertingSensors()
{
  std::vector<Sensor *> alertingSensors;
  for (auto sensor : this->sensors)
    if (sensor->sendAlert())
      alertingSensors.push_back(sensor);
  return alertingSensors;
}

std::vector<Sensor *> Device::getSensorsWithPriceSmallerThanValue(double price)
{
  std::vector<Sensor *> sensorsWithPriceSmallerThanValue;
  for (auto sensor : this->sensors)
    if (sensor->getPrice() < price)
      sensorsWithPriceSmallerThanValue.push_back(sensor);
  return sensorsWithPriceSmallerThanValue;
}

void Device::writeToFile(std::string fileName, double price)
{
  std::ofstream fileStream(fileName);
  std::vector<Sensor *> sensorsWithPriceSmallerThanValue = this->getSensorsWithPriceSmallerThanValue(price);
  std::sort(sensorsWithPriceSmallerThanValue.begin(), sensorsWithPriceSmallerThanValue.end(), compareSensors);
  for (auto sensor : sensorsWithPriceSmallerThanValue)
    fileStream
        << sensor->toString() << '\n';
}