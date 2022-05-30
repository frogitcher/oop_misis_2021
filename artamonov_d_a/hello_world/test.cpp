#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "hello_world.h"

TEST_CASE("Testing HW function.") {
    CHECK(HelloWorld() == "Hello World!");
}
