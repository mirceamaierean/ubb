#pragma once
#include "../service/Service.h"
#include <iostream>
#include <string>

class UI
{
private:
  Service service;

public:
  UI();
  ~UI();
  void printInitialMenu();
  void printAdminMenu();
  void printUserMenu();
  void runApp();
  void printAllMovies();
  void adminAddMovie();
  void adminRemoveMovie();
  void adminUpdateMovie();
};