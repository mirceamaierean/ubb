cmake_minimum_required(VERSION 3.23)
project(test_model_oop)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/mirceamaierean/Qt/6.4.2/macos")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(test_model_oop main.cpp car.h repo.cpp repo.h service.cpp service.h gui.cpp gui.h)
target_link_libraries(test_model_oop
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

