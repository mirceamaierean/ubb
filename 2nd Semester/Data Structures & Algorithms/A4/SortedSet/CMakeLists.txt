cmake_minimum_required(VERSION 3.22.4)
project(SortedSet)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(main
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        SortedSet.cpp
        SortedSet.h
        SortedSetIterator.cpp
        SortedSetIterator.h
        ShortTest.cpp
        ShortTest.h)
