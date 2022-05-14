#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "hello_world.h"
#include <string>

TEST_CASE("testing"){
	CHECK(helloworld() == "hello world");
}
