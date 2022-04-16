#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "hello_world.h"

TEST_CASE("Testing Hello_World")
{
    CHECK(Hello_World() == "Hello World!");
}