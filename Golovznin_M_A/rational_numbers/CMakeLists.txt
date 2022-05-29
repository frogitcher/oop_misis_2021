cmake_minimum_required(VERSION 3.0)
project(rational_numbers)

set(CMAKE_CXX_STANDARD 17)

add_executable(rational rational.cpp rational.h)

add_executable(test_rational test.cpp rational.cpp rational.h)


