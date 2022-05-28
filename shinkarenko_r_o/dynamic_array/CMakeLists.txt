cmake_minimum_required(VERSION 3.0)

project(dynamic_array)

include_directories(doctest)

add_executable(dynamic_array
	test.cpp
	dynamic.cpp
	dynamic.h
)
