cmake_minimum_required(VERSION 3.19)
project(visualAlgo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

qt_add_executable(visualAlgo
    src/main.cpp
    src/mainwindow.cpp
    src/SortCanvas.cpp
    src/BubbleSort.tpp
    src/CountingSort.tpp
    src/HeapSort.tpp
    src/InsertionSort.tpp
    src/MergeSort.tpp
    src/QuickSort.tpp
    src/SelectionSort.tpp
    src/ShakerSort.tpp

    include/mainwindow.h
    include/SortCanvas.h
    include/BubbleSort.h
    include/CountingSort.h
    include/HeapSort.h
    include/InsertionSort.h
    include/MergeSort.h
    include/QuickSort.h
    include/SelectionSort.h
    include/ShakerSort.h
    include/SortAlgorithm.h

    ui/mainwindow.ui)

target_link_libraries(visualAlgo PRIVATE
    Qt::Core
    Qt::Widgets)

target_include_directories(visualAlgo PRIVATE include src ui)
