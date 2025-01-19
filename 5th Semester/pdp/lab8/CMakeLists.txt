cmake_minimum_required(VERSION 3.22.4)
project(mpi)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-g -O0")

# set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/target/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/target/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/target/lib)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(MPI REQUIRED)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

add_executable(main main.cpp DSM.h Subscriber.h message.h)
target_link_libraries(main ${MPI_CXX_LIBRARIES})