cmake_minimum_required(VERSION 3.23)
project(a23_914maiereanmircea C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(a23_914maiereanmircea
        main.c
        Medicine.c
        Medicine.h
        Service.c
        Service.h
        UI.c
        UI.h
        DynamicArray.c
        DynamicArray.h Repository.c Repository.h)
