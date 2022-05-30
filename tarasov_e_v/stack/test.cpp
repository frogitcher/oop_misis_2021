//
// Created by Егор Тарасов on 5/28/22.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack.h"

TEST_CASE_TEMPLATE("Testing constructors", T, int, double, float, long long,
                   unsigned long long) {
  stack<T> a;
  CHECK(a.Size() == 0);

  stack<T> b(a);
  CHECK(b.Size() == a.Size());
}