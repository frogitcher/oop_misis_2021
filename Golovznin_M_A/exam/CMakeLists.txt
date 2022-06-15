cmake_minimum_required(VERSION 3.0)
project(exam)

add_executable(exam DynamicStack.cpp DynamicStack.h)
add_executable(test test.cpp DynamicStack.cpp DynamicStack.h)