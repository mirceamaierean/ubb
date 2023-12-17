#include "UI.h"

void UI::removeAClient()
{
  std::string name;
  std::cout << "Enter the name of the client: ";
  std::cin.ignore();
  getline(std::cin, name);
  this->realEstateAgency.removeClient(name);
}

void UI::showAllClientsAndDwellings()
{
  std::cout << "Clients:\n";
  for (auto client : this->realEstateAgency.getClients())
    std::cout << client->toString() << '\n';

  std::cout << "Dwellings:\n";
  for (auto dwelling : this->realEstateAgency.getDwellings())
    std::cout << dwelling.toString() << '\n';
}

void UI::addDwelling()
{
  double price;
  bool isProfitable = false;
  std::string option;
  std::cout << "Enter the price of the dwelling: ";
  std::cin >> price;
  std::cout << "Is it profitable?(true/false): ";
  std::cin >> option;
  if (option == "true")
    isProfitable = true;
  Dwelling dwelling = this->realEstateAgency.addDwelling(price, isProfitable);
  std::cout << "Interested Clients:\n";
  for (auto client : this->realEstateAgency.getInterstedClients(dwelling))
    std::cout << client->toString() << '\n';
}

void UI::saveClientsToFile()
{
  this->realEstateAgency.writeToFile("clients.txt");
}

void UI::runApp()
{
  int option;
  while (true)
  {
    std::cout << "1) Remove a client\n2) Show all clients and dwellings\n3) Add a dwelling\n4) Save all clients to a file\n5) Exit\nEnter your option: ";
    std::cin >> option;
    if (option == 1)
      this->removeAClient();
    else if (option == 2)
      this->showAllClientsAndDwellings();
    else if (option == 3)
      this->addDwelling();
    else if (option == 4)
      this->saveClientsToFile();
    else if (option == 5)
    {
      std::cout << "Bye!\n";
      return;
    }
    else
      std::cout << "Invalid input\n";
  }
}
