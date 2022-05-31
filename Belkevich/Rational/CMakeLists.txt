cmake_minimum_required(VERSION 3.0)

project(Project_OOP)

include_directories(doctest)

add_executable(test_rat
    rational.cpp
    rational.h
    test.cpp
)