cmake_minimum_required(VERSION 3.23)
project(progremr)

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

add_executable(progremr main.cpp Person.h Issue.h Subject.h Session.cpp Session.h Window.cpp Window.h Observer.h)
target_link_libraries(progremr
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

