cmake_minimum_required(VERSION 3.0)

project(dynamicarray)

include_directories(doctest)

add_executable(test_dynamicarray test.cpp dynamicarray.cpp dynamicarray.h)