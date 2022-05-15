cmake_minimum_required(VERSION 3.23)	
project(dynamic_array)

add_executable(dynamic_array dynamic_array.cpp dynamic_array.h)
add_executable(dynamic_array_test dynamic_array_test.cpp ${PROJECT_SOURCE_DIR}/doctest/doctest.h)
