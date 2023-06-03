cmake_minimum_required(VERSION 3.5)

project(tema8 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        WatchList.h
        WatchList.cpp
        FileWatchList.h
          FileWatchList.cpp

          CSVWatchList.h
          CSVWatchList.cpp

          HTMLWatchList.h
          HTMLWatchList.cpp

          Exceptions.h
          Exceptions.cpp

          Movie.h
          Movie.cpp

          MovieValidator.h
          MovieValidator.cpp

          Repository.h
          Repository.cpp

          FileRepository.h
          FileRepository.cpp

          Service.h
          Service.cpp

          UI.h
          UI.cpp

          Utils.h
          Utils.cpp

         MovieList.h
         MovieList.cpp

         AdminWidget.h
         AdminWidget.cpp

         UserWidget.h
         UserWidget.cpp

         movies.txt
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(tema8
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET tema8 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(tema8 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(tema8
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(tema8 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(tema8 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS tema8
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(tema8)
endif()
