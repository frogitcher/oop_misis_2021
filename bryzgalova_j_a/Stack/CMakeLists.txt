cmake_minimum_required(VERSION 3.23.0)

project(project)

include_directories(doctest)

add_executable(test test.cpp stack.cpp stack.h)
