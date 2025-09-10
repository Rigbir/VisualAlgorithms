cmake_minimum_required(VERSION 3.19)
project(visualAlgorithms LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

file(GLOB SORT_TEMPLATE_AND_HEADERS_FILES
    "src/sortTemplates/*.tpp"
    "include/sortHeaders/*.h"
)

qt_add_executable(visualAlgorithms
    ${SORT_TEMPLATE_AND_HEADERS_FILES}
    src/main.cpp
    src/mainwindow.cpp
    src/SortCanvas.cpp

    include/mainwindow.h
    include/SortCanvas.h

    ui/mainwindow.ui)

target_link_libraries(visualAlgorithms PRIVATE
    Qt::Core
    Qt::Widgets)

target_include_directories(visualAlgorithms PRIVATE include src ui include/sortHeaders src/sortTemplates)
