cmake_minimum_required(VERSION 3.22.4)
project(t2_practice)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(main
  main.cpp
  Appliance.h
  Appliance.cpp
  Service.h
  Service.cpp
  UI.h
  UI.cpp
)
