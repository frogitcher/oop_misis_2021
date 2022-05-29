#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "helloworld.h"

TEST_CASE("Test") {
	CHECK(helloworld() == "hello, world!");
}