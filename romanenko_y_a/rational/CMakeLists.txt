cmake_minimum_required(VERSION 3.0)

project(project)

include_directories(doctest)

add_compile_options(-std=c++17)

add_executable(test_rational
    rational.cpp
    rational.h
    test.cpp
)
