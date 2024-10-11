#include "ui.h"

void UI::addSensor()
{
  std::string option, producer;
  Sensor *sensor = nullptr;

  std::cout << "Choose type of sensor: temperature, humidity, smoke";
  std::cin >> option;

  if (option == "temperature")
  {
    std::cout << "Producer: ";
    std::cin >> producer;
    double length, diameter;
    std::cout << "Length: ";
    std::cin >> length;
    std::cout << "Diameter: ";
    std::cin >> diameter;
    sensor = new TemperatureSensor(producer, diameter, length);
  }
  else if (option == "humidity")
  {
    std::cout << "Producer: ";
    std::cin >> producer;
    sensor = new HumiditySensor(producer);
  }
  else if (option == "smoke")
  {
    std::cout << "Producer: ";
    std::cin >> producer;
    sensor = new SmokeSensor(producer);
  }
  else
    return;
  while (true)
  {
    double recording;
    std::cout << "enter a recording: ";
    std::cin >> recording;
    sensor->addRecording(recording);
    std::cout << "do you want to continue?(yes/no): ";
    std::cin >> option;
    if (option == "no")
      break;
  }
  device.addSensor(sensor);
}

void UI::showAllSensors()
{
  std::cout << "the sensors are: \n";
  for (auto sensor : device.getAllSensors())
    std::cout << sensor->toString() << '\n';
}

void UI::showAllSensorsThatEmitAllerts()
{
  for (auto sensor : device.getAlertingSensors())
    std::cout << sensor->toString() << '\n';
}

void UI::printAllSensorsWithPriceSmallerToFile()
{
  double price;
  std::cout << "Please enter the price: ";
  std::cin >> price;
  device.writeToFile("sensors.txt", price);
}

void UI::runApp()
{
  int option;
  while (true)
  {
    std::cout << "1) add a sensor\n";
    std::cout << "2) show all sensors\n";
    std::cout << "3) show all alerting sensors\n";
    std::cout << "4) print all sensors that have a price smaller than p\n";
    std::cout << "5) exit";
    std::cout << "enter your option: ";
    std::cin >> option;
    if (option == 1)
      this->addSensor();
    else if (option == 2)
      this->showAllSensors();
    else if (option == 3)
      this->showAllSensorsThatEmitAllerts();
    else if (option == 4)
      this->printAllSensorsWithPriceSmallerToFile();
    else
    {
      std::cout << "Bye!\n";
      return;
    }
  }
}
