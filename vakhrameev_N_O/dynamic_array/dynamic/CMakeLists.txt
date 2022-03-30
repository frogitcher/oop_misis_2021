cmake_minimum_required(VERSION 3.0)

project(dynamic_array)

include_directories(doctest)

add_executable(test test.cpp dynamic.cpp class_dynamic_array.h)
