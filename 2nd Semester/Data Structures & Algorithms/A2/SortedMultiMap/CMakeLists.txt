cmake_minimum_required(VERSION 3.22.4)
project(Set)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SortedMultiMap
  App.cpp
  ExtendedTest.cpp
  ExtendedTest.h
  SortedMultiMap.cpp
  SortedMultiMap.h
  SMMIterator.cpp
  SMMIterator.h
  ShortTest.cpp
  ShortTest.h)
