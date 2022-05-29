project(project)
cmake_minimum_required(VERSION 3.0)

include(ExternalProject)
find_package(Git REQUIRED)

add_subdirectory(dynamic)
add_subdirectory(rational)
add_subdirectory(Hello_World)
