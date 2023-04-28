#include "UI.h"
#include <iostream>
#include <vector>

UI::UI()
{
  this->service = Service();
}

UI::~UI()
{
}

void UI::displayOptions()
{
  std::cout << "1) Add a new protein\n";
  std::cout << "2) Show all proteins\n";
  std::cout << "3) Show all proteins with a given name\n";
}

void UI::showAllProteins()
{
  std::vector<Protein> vectorsOfProteins = this->service.getVectorOfProteins();
  for (int index = 0; index < vectorsOfProteins.size(); ++index)
    std::cout << vectorsOfProteins[index].getOrganism() << "|" << vectorsOfProteins[index].getName() << "|" << vectorsOfProteins[index].getAssociatedSequence() << "\n";
}

void UI::showAllProteinsWithAGivenName()
{
  std::string nameOfProtein;
  std::cout << "Enter the name of the protein: ";
  std::cin >> nameOfProtein;
  std::vector<Protein> vectorOfProteins = this->service.getProteinsByName(nameOfProtein);

  if (vectorOfProteins.size() == 0)
  {
    std::cout << "There are no proteins like this!\n";
    return;
  }
  else
  {
    for (int index = 0; index < vectorOfProteins.size(); ++index)
      std::cout << vectorOfProteins[index].getOrganism() << "|" << vectorOfProteins[index].getName() << "|" << vectorOfProteins[index].getAssociatedSequence() << "\n";
  }
}

void UI::addANewProtein()
{
  std::string nameOfProtein, organismOfProtein, associatedSequeneOfProtein;
  std::cout << "Enter the organism of the protein: ";
  std::cin >> organismOfProtein;
  std::cout << "Enter the name of the protein: ";
  std::cin >> nameOfProtein;
  std::cout << "Enter the associated sequence of the protein: ";
  std::cin >> associatedSequeneOfProtein;

  if (this->service.addProteinToRepository(organismOfProtein, nameOfProtein, associatedSequeneOfProtein))
    std::cout << "Protein Added Successfully!\n";
  else
    std::cout << "Protein Already Exists\n";
}

void UI::runApplication()
{
  int command;
  while (true)
  {
    this->displayOptions();
    std::cout << "Enter your command: ";
    std::cin >> command;
    if (command == ADD_PROTEIN_TO_REPOSITORY)
      this->addANewProtein();
    else if (command == DISPLAY_ALL_PROTEINS)
      this->showAllProteins();
    else
      this->showAllProteinsWithAGivenName();
  }
}