cmake_minimum_required(VERSION 3.0)
project(oop)

include_directories(doctest)

add_executable(
	matrix
	test.cpp
	base_matrix.h
	flat_matrix.h
	table_matrix.h
)
