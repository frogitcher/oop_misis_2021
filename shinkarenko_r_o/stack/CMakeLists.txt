cmake_minimum_required(VERSION 3.0)

project(stack)

include_directories(doctest)

add_executable(test_stack
	Stack.h
	Test_stack.cpp
)
