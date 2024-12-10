#pragma once
#include "Service.h"
class UI
{
private:
  const int ADD_PROTEIN_TO_REPOSITORY = 1;
  const int DISPLAY_ALL_PROTEINS = 2;
  const int SHOW_PROTEINS_WITH_GIVEN_NAME = 3;
  Service service;

public:
  UI();
  ~UI();
  void displayOptions();
  void runApplication();
  void addANewProtein();
  void showAllProteins();
  void showAllProteinsWithAGivenName();
};