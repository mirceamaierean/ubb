cmake_minimum_required(VERSION 3.23)
project(practic)

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

add_executable(practic main.cpp department.h volunteer.h repository.cpp repository.h observer.h subject.cpp subject.h session.cpp session.h window.cpp window.h stats.cpp stats.h)
target_link_libraries(practic
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )
