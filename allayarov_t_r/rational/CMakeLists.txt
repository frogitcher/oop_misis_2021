cmake_minimum_required(VERSION 3.23)	
project(rational)

add_library(rational_module rational.cpp)
target_link_libraries(rational_module)

add_executable(rational rational_test.cpp)
target_link_libraries(rational rational_module)

