cmake_minimum_required(VERSION 3.22.4)
project(a23_914maiereanmircea C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(main
        app/main.c
        src/ui/UI.c
        include/ui/UI.h
        src/domain/Medicine.c
        include/domain/Medicine.h
        src/domain/DynamicArray.c
        include/domain/DynamicArray.h
        src/domain/Operation.c
        include/domain/Operation.h
        src/service/Service.c
        include/service/Service.h
        src/repository/UndoRedoRepository.c
        include/repository/UndoRedoRepository.h
        src/repository/Repository.c
        include/repository/Repository.h
        tests/app/AllTests.c
        tests/app/AllTests.h
        tests/src/domain/MedicineTest.c
        tests/include/domain/MedicineTest.h
        tests/src/domain/DynamicArrayTest.c
        tests/include/domain/DynamicArrayTest.h
        tests/src/service/ServiceTest.c
        tests/include/service/ServiceTest.h)