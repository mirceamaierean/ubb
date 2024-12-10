CMAKE_MINIMUM_REQUIRED(VERSION 3.22.4)
PROJECT(a7_914maiereanmircea_1)

SET(CMAKE_CXX_STANDARD 20)
SET(GCC_FLAGS "-lsqlite3")

INCLUDE_DIRECTORIES(.)

SET(CMAKE_EXE_LINKER_FLAGS "${GCC_FLAGS}")

ADD_EXECUTABLE(main
  main.cpp

  WatchList.h
  WatchList.cpp

  FileWatchList.h
  FileWatchList.cpp

  CSVWatchList.h
  CSVWatchList.cpp

  HTMLWatchList.h
  HTMLWatchList.cpp

  Exceptions.h
  Exceptions.cpp

  Movie.h
  Movie.cpp

  MovieValidator.h
  MovieValidator.cpp

  Repository.h
  Repository.cpp

  FileRepository.h
  FileRepository.cpp

  DBRepository.h
  DBRepository.cpp

  Service.h
  Service.cpp

  UI.h
  UI.cpp

  Utils.h
  Utils.cpp

  testMovie.h
  testMovie.cpp

  testRepository.h
  testRepository.cpp

  testService.h
  testService.cpp
)
