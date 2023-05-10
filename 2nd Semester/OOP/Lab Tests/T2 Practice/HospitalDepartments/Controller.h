#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Departments.h"

class Controller
{
private:
  std::vector<HospitalDepartment *> departments;

public:
  Controller()
  {
    HospitalDepartment *neonantalUnitSanovil = new NeonantalUnit("Sanovil", 70, 9);
    HospitalDepartment *neonantalUnitReginaMaria = new NeonantalUnit("Regina Maria", 25, 7);

    HospitalDepartment *surgeryUnitSanovil = new Surgery("Sanovil", 30, 60);
    HospitalDepartment *surgeryUnitReginaMaria = new Surgery("Regina Maria", 10, 10);

    departments.push_back(neonantalUnitSanovil);
    departments.push_back(neonantalUnitReginaMaria);
    departments.push_back(surgeryUnitSanovil);
    departments.push_back(surgeryUnitReginaMaria);
  };
  ~Controller()
  {
    for (auto department : departments)
      delete department;
  };
  static inline bool comparisonFunction(HospitalDepartment *department1, HospitalDepartment *department2);
  void addDepartments(HospitalDepartment *department);
  std::vector<HospitalDepartment *> getAllDepartments();
  std::vector<HospitalDepartment *> getAllEficientDepartments();
  void writeToFile(std::string fileName);
};