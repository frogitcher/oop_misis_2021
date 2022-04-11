#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "hello.h"

TEST_CASE("fact") {
    CHECK(Hello_World() == "Hello World!");
}