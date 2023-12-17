#pragma once
#include "Service.h"
#include "FileWatchList.h"

class TestsService
{
public:
  static void testService(Repository *typeOfRepository, FileWatchList *typeOfWatchList);
  static void testService();
};