#include "Sensor.h"

std::string Sensor::toString()
{
  std::string sensorString = "Producer: ";
  sensorString += producer;
  sensorString += "\nRecordings: ";
  for (auto recording : recordings)
  {
    sensorString += std::to_string(recording);
    sensorString += " ";
  }
  sensorString += "\n";
  return sensorString;
}

void Sensor::addRecording(double recording)
{
  this->recordings.push_back(recording);
}

std::string Sensor::getProducer()
{
  return this->producer;
}

bool TemperatureSensor::sendAlert()
{
  return false;
}

double TemperatureSensor::getPrice()
{
  if (this->diamater < 3 && this->length < 50)
    return 17;
  return 9;
}

std::string TemperatureSensor::toString()
{
  std::string temperatureSensorString = "Type: Temperature Sensor\nDiamater: " + std::to_string(diamater) + "\nLength: " + std::to_string(length) + "\n";
  temperatureSensorString += Sensor::toString();
  return temperatureSensorString;
}

bool HumiditySensor::sendAlert()
{
  int countRecords = 0;
  for (auto recording : recordings)
    if (recording < 10 || recording > 30)
    {
      ++countRecords;
      if (countRecords == 2)
        return true;
    }
  return false;
}

double HumiditySensor::getPrice()
{
  return 4;
}

std::string HumiditySensor::toString()
{
  std::string sensorString = "Type: Humidity Sensor\n";
  sensorString += Sensor::toString();
  return sensorString;
}

bool SmokeSensor::sendAlert()
{
  for (auto recording : recordings)
    if (recording > 1600)
      return true;
  return false;
}

double SmokeSensor::getPrice()
{
  return 25;
}

std::string SmokeSensor::toString()
{
  std::string sensorString = "Type: Smoke Sensor\n";
  sensorString += Sensor::toString();
  return sensorString;
}
