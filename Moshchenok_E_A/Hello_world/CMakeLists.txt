project(project)
cmake_minimum_required(VERSION 3.0)

add_executable(hello_world hello_world.h main.cpp)

add_executable(test_hello_world hello_world.h test.cpp)