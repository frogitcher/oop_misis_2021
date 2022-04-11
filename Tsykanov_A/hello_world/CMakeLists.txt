project(hello_world)
cmake_minimum_required(VERSION 3.0)

include_directories(doctest)

add_executable (main 
	"hello.cpp"
	"hello.h"
)
add_executable (test 
    "test.cpp"
)