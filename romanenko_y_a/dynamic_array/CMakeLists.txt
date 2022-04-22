cmake_minimum_required(VERSION 3.0)

project(project)

include_directories(doctest)

add_executable(test_dynamic_array
    dynamic_array.cpp
    dynamic_array.h
    test.cpp
)