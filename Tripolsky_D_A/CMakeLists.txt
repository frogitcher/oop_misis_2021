cmake_minimum_required(VERSION 3.0)
project(project)

#include(doctest.cmake)
set(DOCTEST_INCLUDE_DIR doctest/doctest)
include_directories(${DOCTEST_INCLUDE_DIR})

add_subdirectory(dynamic_array)

