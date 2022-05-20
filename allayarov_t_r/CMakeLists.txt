cmake_minimum_required(VERSION 3.23)
project(lab)

set(DOCTEST_DIR ${CMAKE_SOURCE_DIR}/doctest)
include_directories(${DOCTEST_DIR})

add_subdirectory(doctest)
add_subdirectory(hello_world)
add_subdirectory(rational)
add_subdirectory(dynamic_array)
