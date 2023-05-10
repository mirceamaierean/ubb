cmake_minimum_required(VERSION 3.22.4)
project(t2_practice_doctors)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(main
  main.cpp
  Departments.h
  Departments.cpp
  Controller.h
  Controller.cpp
  UI.h
  UI.cpp
)
