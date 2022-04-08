cmake_minimum_required(VERSION 3.0)
project(oop)

include_directories(doctest)

add_executable(
	dynamic_array
    test.cpp
    dynamic_array.cpp
    dynamic_array.h
)
