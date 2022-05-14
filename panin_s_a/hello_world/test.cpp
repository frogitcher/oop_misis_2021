#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "hello_world.h"
#include "doctest.h"
#include <string>

TEST_CASE("testing the factorial function") {
    CHECK(HelloWorld() == "Hello World!");
}
