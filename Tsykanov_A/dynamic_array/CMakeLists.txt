
cmake_minimum_required (VERSION 3.0)

include_directories(doctest)

add_executable (main 
	"DynamicArray.cpp"
	"DynamicArray.h"
	"test.cpp"
)
