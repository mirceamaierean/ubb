#include "UI.h"

void UI::runApp()
{
  int option;
  while (true)
  {
    std::cout << "1) Add an appliance\n2) Get all appliances\n3) Get all efficient appliances\n4) Write appliances to file\n5) Exit\n";
    std::cin >> option;
    if (option == 1)
      this->addAppliance();
    else if (option == 2)
      this->showAllApliances();
    else if (option == 3)
      this->showAllEfficientAppliances();
    else if (option == 4)
      this->writeToFile();
    else if (option == 5)
    {
      std::cout << "Bye!\n";
      return;
    }
    else
      std::cout << "invalid option";
  }
}

void UI::addAppliance()
{
  std::string id;
  double weight;
  int option;
  Appliance *appliance;
  std::cout << "1) Refrigerator\n2) DishWasher\nChoose your option: ";
  std::cin >> option;
  if (option == 1)
  {
    std::string electricityUsageClass, optionFreezer;
    bool hasFreezer = true;
    std::cout << "ID: ";
    std::cin.ignore();
    std::getline(std::cin, id);
    std::cout << "Weight: ";
    std::cin >> weight;
    std::cout << "Electricity Usage Class: ";
    std::cin.ignore();
    std::getline(std::cin, electricityUsageClass);
    std::cout << "Does it haver a freezer?(true, false): ";
    std::cin >> optionFreezer;
    if (optionFreezer == "false")
      hasFreezer = false;
    appliance = new Refrigerator(id, weight, electricityUsageClass, hasFreezer);
  }
  else if (option == 2)
  {
    double washingCycleLength, consumedElectricityForOneHour;
    bool hasFreezer = true;
    std::cout << "ID: ";
    std::cin.ignore();
    std::getline(std::cin, id);
    std::cout << "Weight: ";
    std::cin >> weight;
    std::cout << "Washing Cycle Length: ";
    std::cin >> washingCycleLength;
    std::cout << "Consumed Electricity For One Hour: ";
    std::cin >> consumedElectricityForOneHour;
    appliance = new DishWasher(id, weight, washingCycleLength, consumedElectricityForOneHour);
  }
  this->service.addAppliance(appliance);
}

void UI::showAllApliances()
{
  std::cout << "Apliances:\n";
  for (auto appliance : this->service.getAllApliances())
    std::cout << appliance->toString() << '\n';
}

void UI::showAllEfficientAppliances()
{
  double consumedElectricity;
  std::cout << "Enter the quantity of consumed electricity: ";
  std::cin >> consumedElectricity;
  for (auto appliance : this->service.getAllWithConsumedElectricityLessThan(consumedElectricity))
    std::cout << appliance->toString() << '\n';
}

void UI::writeToFile()
{
  double consumedElectricity;
  std::cout << "Enter the quantity of consumed electricity: ";
  std::cin >> consumedElectricity;
  this->service.writeToFile("appliances.txt", consumedElectricity);
}
