cmake_minimum_required(VERSION 3.22.4)
project(a45_914maiereanmircea)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(main
        app/main.cpp
        include/domain/DynamicVector.h
        include/domain/Movie.h
        include/repository/Repository.h
        include/service/Service.h
        include/ui/UI.h
        src/domain/Movie.cpp
        src/repository/Repository.cpp
        src/service/Service.cpp
        src/ui/UI.cpp
        tests/include/domain/testDynamicVector.h
        tests/src/domain/testDynamicVector.cpp
        tests/include/domain/testMovie.h
        tests/src/domain/testMovie.cpp
        tests/include/repository/testRepository.h
        tests/src/repository/testRepository.cpp
        tests/src/domain/testMovie.cpp
        tests/include/service/testService.h
        tests/src/service/testService.cpp
)
