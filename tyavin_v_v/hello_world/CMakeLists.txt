cmake_minimum_required(VERSION 3.0)

project(project)

include_directories(doctest)

add_executable(main
	main.cpp
	hello_world.h
)

add_executable(test_hello
	test.cpp
)
