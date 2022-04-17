cmake_minimum_required(VERSION 3.23.0)

project(project)

include_directories(doctest)

add_executable(dynamic_array test.cpp dynamic_array.h dynamic_array.cpp)
