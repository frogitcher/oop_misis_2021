cmake_minimum_required(VERSION 3.0)

project(project)

include_directories(doctest)

add_executable(test_dynamic
  dynamic.cpp
  dynamic.h
  test.cpp
)