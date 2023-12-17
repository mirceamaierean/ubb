cmake_minimum_required(VERSION 3.22.4)
project(matrixSLLA)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(main Matrix.h Matrix.cpp ShortTest.h ShortTest.cpp ExtendedTest.h ExtendedTest.cpp App.cpp)
