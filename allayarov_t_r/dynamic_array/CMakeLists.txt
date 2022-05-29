cmake_minimum_required(VERSION 3.23)	
project(dynamic_array)

add_library(da_module dynamic_array.cpp)
target_link_libraries(da_module)

add_executable(dynamic_array dynamic_array_test.cpp)
target_link_libraries(dynamic_array da_module)
