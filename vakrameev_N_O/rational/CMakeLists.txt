cmake_minimum_required(VERSION 3.0)

project(rational_nums)

include_directories(doctest)

add_executable(rational rational.cpp class_rational.h)

add_executable(test test.cpp)
