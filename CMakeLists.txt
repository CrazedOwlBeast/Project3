cmake_minimum_required(VERSION 3.17)
project(SortingBenchmarking)

set(CMAKE_CXX_STANDARD 14)

add_executable(SortingBenchmarking main.cpp matplotlibcpp.h randomizer.h sorting.h)

find_package(Python3 COMPONENTS Development NumPy)
target_include_directories(SortingBenchmarking PRIVATE ${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})
target_link_libraries(SortingBenchmarking Python3::Python Python3::NumPy)