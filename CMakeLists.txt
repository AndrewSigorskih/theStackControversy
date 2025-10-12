cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(theStackControversy)

enable_testing()

add_subdirectory(main)
add_subdirectory(test)
add_subdirectory(libstackcollection)
