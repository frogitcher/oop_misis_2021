cmake_minimum_required(VERSION 3.0)

project(project)

add_executable(
        main
        dyn_array.cpp
        dyn_array.h
)

add_executable(
        test
        test.cpp
)