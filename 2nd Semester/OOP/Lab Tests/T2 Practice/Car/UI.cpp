#include "UI.h"

void UI::addCar()
{
  std::string bodyStyle, engineType, fuelType;
  int autonomy = 0;
  std::cout << "Enter Body Style: ";
  std::cin >> bodyStyle;
  std::cout << "Enter Engine Style: ";
  std::cin >> engineType;
  if (engineType == "Electric")
  {
    std::cout << "Enter Autonomy: ";
    std::cin >> autonomy;
    fuelType = "Electric";
  }
  else if (engineType == "Turbo")
  {
    std::cout << "Enter Fuel Type: ";
    std::cin >> fuelType;
  }
  this->service.addCar(bodyStyle, engineType, fuelType, autonomy);
  std::cout << "The price of this car is " << this->service.getLastAddedCar().computePrice() << '\n';
}

void UI::showAllCars()
{
  for (auto car : this->service.getAllCars())
    std::cout << car.toString() << "\n";
}

void UI::writeCarsWithSmallerPriceToFile()
{
  double price;
  std::cout << "Enter your desired price: ";
  std::cin >> price;
  this->service.writeToFile("cars.txt", this->service.getCarsWithMaximumPrice(price));
}

void UI::runApp()
{
  int option;
  while (true)
  {
    std::cout << "1) Add new car\n2) Show all cars\n3) Save cars to file\n4) Exit app\n";
    std::cin >> option;
    if (option == 1)
      this->addCar();
    else if (option == 2)
      this->showAllCars();
    else if (option == 3)
      this->writeCarsWithSmallerPriceToFile();
    else if (option == 4)
    {
      std::cout << "Goodbye!\n";
      return;
    }
    else
      std::cout << "Invalid input!\n";
  }
}
