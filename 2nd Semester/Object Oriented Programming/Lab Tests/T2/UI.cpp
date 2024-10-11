#include "UI.h"

void UI::runApp()
{
  int option = 1;
  while (true)
  {
    std::cout << "1) Add a new car\n2) Show all cars\n3) Save to a file all the cars with a prices less than a given price\n4) Exit\nChoose your option: ";
    std::cin >> option;
    if (option == 1)
      this->addCar();
    else if (option == 2)
      this->showAllCars();
    else if (option == 3)
      this->writeCarsToFile();
    else if (option == 4)
    {
      std::cout << "Bye!\n";
      return;
    }
    else
      std::cout << "Invalid option!\n";
  }
}

void UI::showAllCars()
{
  std::cout << "Available Cars: \n";
  for (auto car : this->service.getAllCars())
    std::cout << car.toString() << '\n';
}

void UI::addCar()
{
  int autonomy = 0;
  std::string bodyStyle, engineType;
  std::cout << "Enter the body style: ";
  std::cin >> bodyStyle;
  std::cout << "Enter the type of the Engine: ";
  std::cin >> engineType;
  if (engineType == "Electric")
  {
    std::cout << "Enter the autonomy of the Engine: ";
    std::cin >> autonomy;
  }
  this->service.addCar(bodyStyle, engineType, autonomy);
  std::cout << "Car added successfully, The price of this car is " << std::to_string(this->service.getPriceOfLastCarAdded()) << '\n';
}

void UI::writeCarsToFile()
{
  double price;
  std::cout << "Enter the price: ";
  std::cin >> price;
  this->service.writeToFile("cars.txt", this->service.getCarsWithMaxPrice(price));
}
