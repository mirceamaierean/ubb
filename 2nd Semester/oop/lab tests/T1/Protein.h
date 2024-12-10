#pragma once
#include <iostream>

class Protein
{
private:
  std::string organism;
  std::string name;
  std::string associatedSequence;

public:
  Protein(const std::string &organism, const std::string &name, const std::string &associatedSequence);
  Protein(const Protein &protein);
  ~Protein();
  void setOrganism(const std::string &organism);
  void setName(const std::string &name);
  void setAssociatedSequence(const std::string &associatedSequence);
  std::string getOrganism();
  std::string getName();
  std::string getAssociatedSequence();
  bool operator<(const Protein &protein) const;
  bool operator==(const Protein &protein) const;
};