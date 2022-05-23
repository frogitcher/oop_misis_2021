add_library(rational rational.h rational.cpp)

add_executable(rational_test test.cpp)
target_link_libraries(rational_test rational)
