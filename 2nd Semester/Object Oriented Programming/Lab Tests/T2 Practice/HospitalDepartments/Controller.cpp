#include "Controller.h"

inline bool Controller::comparisonFunction(HospitalDepartment *department1, HospitalDepartment *department2)
{
  return department1->getName() < department2->getName();
}

void Controller::addDepartments(HospitalDepartment *department)
{
  this->departments.push_back(department);
}

std::vector<HospitalDepartment *> Controller::getAllDepartments()
{
  return this->departments;
}

std::vector<HospitalDepartment *> Controller::getAllEficientDepartments()
{
  std::vector<HospitalDepartment *> efficientDepartments;
  for (auto department : this->departments)
    if (department->isEficient())
      efficientDepartments.push_back(department);
  return efficientDepartments;
}

void Controller::writeToFile(std::string fileName)
{
  std::sort(this->departments.begin(), this->departments.end(), comparisonFunction);
  std::ofstream writeToFile(fileName);
  for (auto department : this->departments)
    writeToFile << department->toString() << '\n';
}
