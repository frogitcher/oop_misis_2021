cmake_minimum_required(VERSION 3.0)

project(project)

include_directories(doctest)

add_executable (dyn_array
    dynamic_array.cpp
    dynamic_array.h
    tests.cpp
)