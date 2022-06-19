cmake_minimum_required(VERSION 3.0)

project(project)


add_executable(main 
	main.cpp
	DynamicArray.h
	DynamicArrayMethods.cpp
)

add_executable(test
	test.cpp
)

