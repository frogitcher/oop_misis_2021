cmake_minimum_required(VERSION 3.0)
project(hello_world)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp hello_world.h)

add_executable(test_hello test.cpp)


