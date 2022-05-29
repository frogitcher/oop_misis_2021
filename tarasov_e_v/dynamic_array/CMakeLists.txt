project(rational_numbers)
cmake_minimum_required(VERSION 3.0)
add_compile_options(-std=c++17)

include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(
        doctest
        PREFIX ${CMAKE_BINARY_DIR}/doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        TIMEOUT 10
        UPDATE_COMMAND ${GIT_EXECUTABLE} pull
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
)

# Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
ExternalProject_Get_Property(doctest source_dir)
set(DOCTEST_INCLUDE_DIR ${source_dir}/doctest CACHE INTERNAL "Path to include folder for doctest")
include_directories(${DOCTEST_INCLUDE_DIR})


add_executable(test
        dynamicarray.cpp
        test.cpp
        )
# add_subdirectory(tarasov_e_v)