#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack.h"

TEST_CASE("Testing the constructors")
{
  Stack<double> b({1.1, 1.2, 1.3, 1.4, 1.5});
  CHECK(b.Size() == 5);
  CHECK(b.Get() == 1.5);

  Stack<double> c(b);
  CHECK(b.Size() == 5);
  CHECK(b.Get() == 1.5);
}

TEST_CASE("Testing the operators")
{
  Stack<int> a({1, 2, 3, 4, 5, 6});
  Stack<int> b({10, 20});
  b = a;
  Stack<int> c({1, 2, 3, 4, 5});
  CHECK_EQ(a, b);
  CHECK_NE(b, c);
}


TEST_CASE("Testing the methods")
{
  Stack<int> a({1, 2, 3, 4, 5});
  a.Push(6);
  for (int i=a.Size(); !a.Empty(); --i)
  { 
    CHECK_EQ(a.Get(), i);
    a.Pop();
  }
  CHECK(a.Empty());
  Stack<int> b({100, 200, 300});
  Stack<int> c({400, 500, 600});
  Stack<int> d({100, 200, 300, 600, 500, 400});
  b.Merge(c);
  CHECK_EQ(b, d);
  d.Clear();
  CHECK(d.Size()==0);
  Stack<int> i({10});
  Stack<int> j({20});
  i.Swap(j);
  CHECK(i.Get() == 20);
  CHECK(j.Get() == 10);
}

TEST_CASE("Testing the exceptions")
{
  Stack<int> a({1});
  a.Pop();
  CHECK_THROWS_WITH(a.Pop(), "Stack is empty. Can not pop the last element");
  CHECK_THROWS_WITH(a.Get(), "Stack is empty");
}