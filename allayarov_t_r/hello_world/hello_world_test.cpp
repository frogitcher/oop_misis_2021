#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "hello_world.h"

#include "doctest.h"

TEST_CASE("[hello_world] - testing HelloWorld function")
{
  CHECK(HelloWorld() == "Hello World!");
}