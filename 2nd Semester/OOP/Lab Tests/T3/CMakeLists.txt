cmake_minimum_required(VERSION 3.23)
project(t3_914maiereanmircea)

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

add_executable(t3_914maiereanmircea main.cpp document.h Repository.cpp Repository.h Service.cpp Service.h gui.cpp gui.h)
target_link_libraries(t3_914maiereanmircea
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

