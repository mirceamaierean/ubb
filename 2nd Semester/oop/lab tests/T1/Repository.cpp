#include "Repository.h"

Repository::Repository()
{
  this->vectorsWithProteins = std::vector<Protein>();
  Protein protein = Protein("1", "1", "1");
  vectorsWithProteins.push_back(protein);
  protein = Protein("2", "2", "2");
  vectorsWithProteins.push_back(protein);
  protein = Protein("3", "3", "3");
  vectorsWithProteins.push_back(protein);
  protein = Protein("4", "4", "4");
  vectorsWithProteins.push_back(protein);
  protein = Protein("5", "5", "5");
  vectorsWithProteins.push_back(protein);
}

Repository::~Repository()
{
}

Repository &Repository::operator=(const Repository &repository)
{
  this->vectorsWithProteins = repository.vectorsWithProteins;
  return *this;
}

void Repository::addProteinToRepository(Protein protein)
{
  this->vectorsWithProteins.push_back(protein);
}

std::vector<Protein> Repository::getVectorOfProteins()
{
  return this->vectorsWithProteins;
}

int Repository::returnIndexOfProtein(Protein protein)
{
  for (int index = 0; index < this->vectorsWithProteins.size(); ++index)
  {
    if (this->vectorsWithProteins[index] == protein)
      return index;
  }
  return INDEX_NOT_FOUND;
}