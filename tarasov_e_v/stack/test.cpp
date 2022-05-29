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
  CHECK(a.get_head() == nullptr);
  // CHECK(Get_Tail(a) == nullptr);

  stack<T> b(a);
  CHECK(b.Size() == a.Size());
  //    CHECK(b == a);
  //
  //    Stack<T> c(std::initializer_list<T>{ (T)6.4f, (T)-87.001, 3, 0 });
  //    CHECK(c != b);
  //    CHECK_FALSE(c == a);
}