cmake_minimum_required(VERSION 3.22.4)
project(t2_914maiereanmircea_1)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(main
  main.cpp
  Engine.h
  Engine.cpp
  Car.h
  Car.cpp
  Service.h
  Service.cpp
  UI.h
  UI.cpp
)
