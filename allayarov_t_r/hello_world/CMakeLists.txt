cmake_minimum_required(VERSION 3.23)	
project(hello_world)

add_executable(hello_world hello_world.cpp hello_world.h)
add_executable(hello_world_test hello_world_test.cpp ${PROJECT_SOURCE_DIR}/doctest/doctest.h)
