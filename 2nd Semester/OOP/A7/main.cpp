#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include "testMovie.h"
#include "testRepository.h"
#include "testService.h"
#include "UI.h"

int main()
{
  TestsMovie::testMovie();
  TestsRepository::testRepository();
  TestsService::testService();

  UI ui;
  ui.runApp();

  return 0;
}