cmake_minimum_required(VERSION 3.22.4)
project(seminar_project)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(seminar_project
  main.cpp
  DynamicVector.h
  Song.h
  Song.cpp
  Tests.h
  Tests.cpp
)
