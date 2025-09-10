cmake_minimum_required(VERSION 3.19)
project(VisualAlgorithms LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(MACOSX_BUNDLE_ICON_FILE icon.icns)
set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/appIcon/icon.icns")
set_source_files_properties(${app_icon_macos} PROPERTIES
       MACOSX_PACKAGE_LOCATION "Resources")

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

file(GLOB SORT_TEMPLATE_AND_HEADERS_FILES
    "src/sortTemplates/*.tpp"
    "include/sortHeaders/*.h"
)

qt_add_resources(VisualAlgorithms_resources ui/resources.qrc)

qt_add_executable(VisualAlgorithms
    MACOSX_BUNDLE
    ${app_icon_macos}
    ${VisualAlgorithms_resources}
    ${SORT_TEMPLATE_AND_HEADERS_FILES}
    src/main.cpp
    src/mainwindow.cpp
    src/SortCanvas.cpp

    include/mainwindow.h
    include/SortCanvas.h

    ui/mainwindow.ui)

target_link_libraries(VisualAlgorithms PRIVATE
    Qt::Core
    Qt::Widgets)

target_include_directories(VisualAlgorithms PRIVATE include src ui include/sortHeaders src/sortTemplates)
