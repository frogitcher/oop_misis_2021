cmake_minimum_required(VERSION 3.23)	
project(rational)

add_executable(rational rational.cpp rational.h)
add_executable(rational_test rational_test.cpp ${PROJECT_SOURCE_DIR}/doctest/doctest.h)
