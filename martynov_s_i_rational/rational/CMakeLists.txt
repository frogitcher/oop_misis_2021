cmake_minimum_required(VERSION 3.0)

project(numbers)

add_executable(numbers 
	Numbers.cpp 
	Numbers.h
)

add_executable(test_rational 
	test.cpp
)