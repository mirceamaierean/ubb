#include "UI.h"

void UI::runApp()
{
  int option;
  while (1)
  {
    std::cout << "1) Add a new department\n2) Show all departments\n3) Show all efficient departments\n4) Write all the departments to a file\n5) Exit the applciation\nSelect you option: ";
    std::cin >> option;
    if (option == 1)
      this->addDepartment();
    else if (option == 2)
      this->showAllDepartments();
    else if (option == 3)
      this->showAllEfficientDeparments();
    else if (option == 4)
      this->writeToFile();
    else if (option == 5)
    {
      std::cout << "Goodbye!\n";
      return;
    }
    else
      std::cout << "Invalid Option\n";
  }
}

void UI::addDepartment()
{
  int option;
  std::cout << "1) NeoNatalUnit\n2) SurgeryUnit\nSelect your type:\n";
  std::cin >> option;
  if (option == 1)
  {
    std::string nameOfHospital;
    int numberOfDoctors;
    double averageGrade;
    std::cout << "Enter the name of the hospital: ";
    std::cin >> nameOfHospital;
    std::cout << "Enter the number of doctors: ";
    std::cin >> numberOfDoctors;
    std::cout << "Enter the average grade: ";
    std::cin >> averageGrade;
    this->applicationController.addDepartments(new NeonantalUnit(nameOfHospital, numberOfDoctors, averageGrade));
  }
  else if (option == 2)
  {
    std::string nameOfHospital;
    int numberOfDoctors, numberOfPacients;
    std::cout << "Enter the name of the hospital: ";
    std::cin >> nameOfHospital;
    std::cout << "Enter the number of doctors: ";
    std::cin >> numberOfDoctors;
    std::cout << "Enter the number of pacients: ";
    std::cin >> numberOfPacients;
    this->applicationController.addDepartments(new Surgery(nameOfHospital, numberOfDoctors, numberOfPacients));
  }
  else
  {
    std::cout << "Invalid option. Try again!\n";
    return;
  }
}

void UI::showAllDepartments()
{
  std::vector<HospitalDepartment *> departments = this->applicationController.getAllDepartments();
  for (auto department : departments)
    std::cout << department->toString() << '\n';
}

void UI::showAllEfficientDeparments()
{
  std::vector<HospitalDepartment *> departments = this->applicationController.getAllEficientDepartments();
  for (auto department : departments)
    std::cout << department->toString() << '\n';
}

void UI::writeToFile()
{
  std::string filename;
  std::cout << "Enter the name of the file: ";
  std::cin >> filename;
  this->applicationController.writeToFile(filename);
}
