cmake_minimum_required(VERSION 3.0)

project(project)

include_directories(doctest)

add_executable(test_stack
	stack.h
	test.cpp
)
