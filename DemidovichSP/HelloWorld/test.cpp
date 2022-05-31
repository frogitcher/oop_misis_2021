#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "helloWorld.h"
#include "doctest.h"

TEST_CASE("testing hello world") {
    CHECK(helloWorld() == "Hello World!");
}