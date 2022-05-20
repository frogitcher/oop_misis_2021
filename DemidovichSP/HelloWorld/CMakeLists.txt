project(HelloWorld)
cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 14)
add_compile_options(-std=c++17)


add_executable(HelloWorld
        doctest.h
        test.cpp
        helloWorld.cpp
        helloWorld.h)
