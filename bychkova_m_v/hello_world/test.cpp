#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "hello_world.h"
#include <string>

TEST_CASE("testing the hello function") {
    CHECK(Helloworld() == "Hello World!");
}
