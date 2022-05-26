cmake_minimum_required(VERSION 3.0)
project(dynamic_arrays)

add_executable(dynamic_array dynamic_array.cpp dynamic_array.h)

add_executable(test_dynamic test.cpp dynamic_array.cpp)

