#pragma once
#include "Repository.h"
#include "Protein.h"
#include <iostream>

class Service
{
private:
  const int INDEX_NOT_FOUND = -1;
  Repository repository;

public:
  Service();
  ~Service();
  Service &operator=(const Service &service);
  bool addProteinToRepository(std::string organism, std::string name, std::string associatedSequence);
  std::vector<Protein> getVectorOfProteins();
  std::vector<Protein> getProteinsByName(std::string nameOfProtein);
};