#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "hello_world.h"

TEST_CASE("testing func") {
    CHECK(HelloWorld() == "Hello World!");
}
