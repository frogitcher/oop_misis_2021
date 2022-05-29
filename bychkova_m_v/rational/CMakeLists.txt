cmake_minimum_required(VERSION 3.0)

project(project)

include_directories(doctest)

add_executable(testing_rational
		rational.cpp
		rational.h
		test.cpp
)