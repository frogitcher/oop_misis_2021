cmake_minimum_required(VERSION 3.0)
add_compile_options(-std=c++17)


add_executable(dynamic_tests
        dynamicarray.h
        dynamicarray.cpp
        test.cpp
        )