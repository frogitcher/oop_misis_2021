cmake_minimum_required(VERSION 3.0)

project(project)

include_directories(doctest)

add_executable(test 
	rational.cpp
	test.cpp
	rational.h
)