#pragma once
#include "Protein.h"
#include <iostream>
#include <vector>

class Repository
{
private:
  const int INDEX_NOT_FOUND = -1;
  std::vector<Protein> vectorsWithProteins;

public:
  Repository();
  ~Repository();
  Repository &operator=(const Repository &repository);
  void addProteinToRepository(Protein protein);
  void deleteProteinFromRepository(Protein protein);
  int returnIndexOfProtein(Protein protein);
  std::vector<Protein> getVectorOfProteins();
};