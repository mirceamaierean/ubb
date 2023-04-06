#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include "../tests/include/domain/testMovie.h"
#include "../tests/include/repository/testRepository.h"
#include "../tests/include/service/testService.h"
#include "../include/ui/UI.h"

int main()
{
  TestsMovie::testMovie();
  TestsRepository::testRepository();
  TestsService::testService();

  UI ui;
  ui.runApp();

  return 0;
}