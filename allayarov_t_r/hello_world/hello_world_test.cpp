#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include "hello_world.h"

TEST_CASE("[hello_world] - testing HelloWorld function")
{
  CHECK(HelloWorld() == "Hello World!");
}