cmake_minimum_required(VERSION 3.23)	
project(hello_world)

add_library(hw_module hello_world.cpp)
target_link_libraries(hw_module)

add_executable(hello_world hello_world_test.cpp)
target_link_libraries(hello_world hw_module)

