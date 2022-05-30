cmake_minimum_required (VERSION 3.0)

include_directories(doctest)

add_executable (main 
	"Rational_numbers.cpp"
	"Rational_numbers.h"
	"test.cpp"
)

