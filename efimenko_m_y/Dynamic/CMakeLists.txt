add_library(dynamic dynamic.h dynamic.cpp)

add_executable(dynamic_test dynamic_test.cpp)
target_link_libraries(dynamic_test dynamic)