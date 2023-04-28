#include "Protein.h"

Protein::Protein(const std::string &organism, const std::string &name, const std::string &associatedSequence)
{
  this->organism = organism;
  this->name = name;
  this->associatedSequence = associatedSequence;
}

Protein::Protein(const Protein &protein)
{
  this->organism = protein.organism;
  this->name = protein.name;
  this->associatedSequence = protein.associatedSequence;
}

Protein::~Protein()
{
}

std::string Protein::getOrganism()
{
  return this->organism;
}

std::string Protein::getName()
{
  return this->name;
}

std::string Protein::getAssociatedSequence()
{
  return this->associatedSequence;
}

void Protein::setOrganism(const std::string &organism)
{
  this->organism = organism;
}

void Protein::setName(const std::string &name)
{
  this->name = name;
}

void Protein::setAssociatedSequence(const std::string &associatedSequence)
{
  this->associatedSequence = associatedSequence;
}

bool Protein::operator<(const Protein &protein) const
{
  return this->organism < protein.organism;
}

bool Protein::operator==(const Protein &protein) const
{
  return this->organism == protein.organism && this->name == protein.name;
}