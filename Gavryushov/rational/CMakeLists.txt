cmake_minimum_required (VERSION 3.23.0-rc2)
project(project)
add_compile_options(-std=c++17)
include_directories(doctest)


add_executable(test test.cpp rational.h rational.cpp)


