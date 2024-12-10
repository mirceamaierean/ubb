cmake_minimum_required(VERSION 3.23)
project(stars)

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

add_executable(stars main.cpp Astronaut.h Star.h Repository.cpp Repository.h Service.cpp Service.h AstronautWindow.cpp AstronautWindow.h starsModels.cpp starsModels.h)
target_link_libraries(stars
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

