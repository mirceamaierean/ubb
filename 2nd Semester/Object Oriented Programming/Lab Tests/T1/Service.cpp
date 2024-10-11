#include "Service.h"
#include <algorithm>

Service::Service()
{
  this->repository = Repository();
}

Service::~Service()
{
}

Service &Service::operator=(const Service &service)
{
  this->repository = service.repository;
  return *this;
}

bool Service::addProteinToRepository(std::string organism, std::string name, std::string associatedSequence)
{
  Protein proteinToBeAdded = Protein(organism, name, associatedSequence);
  int indexOfProtein = this->repository.returnIndexOfProtein(proteinToBeAdded);
  std::cout << indexOfProtein << '\n';
  if (!this->repository.getVectorOfProteins().empty() && this->repository.returnIndexOfProtein(proteinToBeAdded) != INDEX_NOT_FOUND)
    return false;
  this->repository.addProteinToRepository(proteinToBeAdded);
  return true;
}

std::vector<Protein> Service::getProteinsByName(std::string nameOfProtein)
{
  std::vector<Protein> vectorOfProteinsByName, vectorOfProteins = this->repository.getVectorOfProteins();
  for (int index = 0; index < vectorOfProteins.size(); ++index)
    if (vectorOfProteins[index].getName() == nameOfProtein)
      vectorOfProteinsByName.push_back(vectorOfProteins[index]);
  std::sort(vectorOfProteinsByName.begin(), vectorOfProteinsByName.end());
  return vectorOfProteinsByName;
}

std::vector<Protein> Service::getVectorOfProteins()
{
  return this->repository.getVectorOfProteins();
}