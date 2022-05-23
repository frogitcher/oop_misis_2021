cmake_minimum_required(VERSION 3.0)
project(oop)

include_directories(doctest)

add_executable(
	rational_test
	test.cpp
	rational.cpp
	rational.h
)
