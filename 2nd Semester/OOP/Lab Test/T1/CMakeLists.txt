cmake_minimum_required(VERSION 3.22.4)
project(t1_914maiereanmircea-1)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(main
  main.cpp
  Service.h
  Service.cpp
  Repository.h
  Repository.cpp
  Protein.h
  Protein.cpp
  UI.h
  UI.cpp
  Tests.h
  Tests.cpp
)
