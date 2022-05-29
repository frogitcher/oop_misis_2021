#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "stack.h"

#include "doctest.h"

TEST_CASE("Testing Stack constructors and operators")
{
  Stack<int> stack({1, 2, 3});
  Stack<int> stack1({1, 2, 3});
  CHECK(stack == stack1);

  Stack<int> stack2;
  Stack<int> stack3;
  CHECK(stack2 == stack3);

  Stack<int> stack4 = {4, 5, 6};
  Stack<int> stack5 = {4, 5, 6};
  CHECK(stack4 == stack5);

  Stack<int> stack6 = Stack<int>({7, 8, 9});
  Stack<int> stack7 = Stack<int>({7, 8, 9});
  CHECK(stack6 == stack7);

  Stack<int> stack8({10, 11, 12});
  Stack<int> stack9(stack8);
  Stack<int> stack10(stack9);
  CHECK(stack8 == stack9);
  CHECK(stack9 == stack10);
  CHECK(stack8.size() == stack9.size());
  CHECK(stack9.size() == stack10.size());

  CHECK(stack1 != stack2);
  CHECK(stack3 != stack4);
  CHECK(stack5 != stack6);
  CHECK(stack6 != stack8);
  CHECK(stack7 != stack10);

  Stack<int> stack11({13, 14, 15});
  Stack<int> stack12(stack11);
  Stack<int> stack13 = stack11;
  CHECK(stack12 == stack13);
  CHECK(stack12.size() == stack13.size());

  Stack<int> stack14 = Stack<int>({16, 17, 18});
  Stack<int> stack15(stack14);
  CHECK(stack14 == stack15);
  CHECK(stack14.size() == stack15.size());

  Stack<int> stack16({19, 20});
  Stack<int> stack17 = {19, 20};
  Stack<int> stack18 = Stack<int>({19, 20});
  CHECK(stack16 == stack17);
  CHECK(stack16 == stack18);
  CHECK(stack17 == stack18);
  CHECK(stack16.size() == stack17.size());
  CHECK(stack17.size() == stack18.size());

  Stack<int> stack19({19});
  Stack<int> stack20 = Stack<int>({19});
  CHECK(stack19 == stack20);
  CHECK(stack19.size() == stack20.size());

  Stack<int> stack21;
  Stack<int> stack22({});
  Stack<int> stack23(stack21);
  Stack<int> stack24 = Stack<int>();
  CHECK(stack21 == stack22);
  CHECK(stack21 == stack23);
  CHECK(stack21 == stack24);
  CHECK(stack22 == stack23);
  CHECK(stack22 == stack24);
  CHECK(stack23 == stack24);
  CHECK(stack21.size() == stack22.size());
  CHECK(stack21.size() == stack23.size());
  CHECK(stack21.size() == stack24.size());
  CHECK(stack22.size() == stack23.size());
  CHECK(stack22.size() == stack24.size());
  CHECK(stack23.size() == stack24.size());
}

TEST_CASE("Testing Stack methods #1")
{
  Stack<int> stack{1, 2, 3};
  CHECK(stack.size() == 3);
  CHECK(stack.empty() == false);

  Stack<int> stack1;
  CHECK(stack1.size() == 0);
  CHECK(stack1.empty() == true);

  stack1.push(1);
  CHECK(stack1.size() == 1);
  CHECK(stack1.empty() == false);

  stack1.push(2);
  stack1.push(3);
  CHECK(stack1 == stack);

  stack.pop();
  stack.pop();
  stack.pop();
  CHECK(stack.size() == 0);
  CHECK(stack.empty() == true);
}

TEST_CASE("Testing Stack methods #2")
{
  Stack<int> stack(Stack<int>({53, -10, 97}));
  CHECK(stack.get() == 97);
  stack.pop();
  CHECK(stack.get() == -10);
  stack.pop();
  CHECK(stack.get() == 53);
  stack.pop();
  CHECK_THROWS(stack.get());
  CHECK_THROWS(stack.pop());
}

TEST_CASE("Testing Stack methods #3")
{
  Stack<int> stack1 = Stack<int>({0, -1, 7});
  Stack<int> stack2 = Stack<int>({99, 5, 5, 2, 9});

  stack1.swap(stack2);
  CHECK(stack1 == Stack<int>({99, 5, 5, 2, 9}));
  CHECK(stack2 == Stack<int>({0, -1, 7}));

  stack1.clear();
  stack2.clear();
  CHECK(stack1 == stack2);
  CHECK(stack1.size() == 0);
  CHECK(stack2.empty() == true);

  stack1.swap(stack2);
  CHECK(stack1 == stack2);
  CHECK(stack1.size() == 0);
  CHECK(stack2.empty() == true);
}

TEST_CASE("Testing Stack methods #4")
{
  Stack<int> stack1 = Stack<int>({0, -1, 7});
  Stack<int> stack2 = Stack<int>({99, 5, 5, 2, 9});

  stack1.merge(stack2);
  CHECK(stack1.size() == 8);

  std::ostringstream oss;
  while (!stack1.empty())
  {
    oss << stack1.get() << " ";
    stack1.pop();
  }
  CHECK(oss.str() == "7 -1 0 9 2 5 5 99 ");
  CHECK(stack2.empty() == true);

  Stack<int> stack3;
  Stack<int> stack4;

  stack3.merge(stack4);
  CHECK(stack3.empty() == true);
  CHECK(stack3.size() == 0);
  CHECK(stack4.empty() == true);
  CHECK(stack4.size() == 0);

  Stack<int> stack5;
  Stack<int> stack6({1});

  stack5.merge(stack6);
  CHECK(stack5 == Stack<int>{1});
  CHECK(stack5.size() == 1);
  CHECK(stack6.empty() == true);
  CHECK(stack6.size() == 0);

  Stack<int> stack7 = Stack<int>{9, -14};
  Stack<int> stack8;

  stack7.merge(stack8);
  CHECK(stack7 == Stack<int>{9, -14});
  CHECK(stack7.size() == 2);
  CHECK(stack8.empty() == true);
  CHECK(stack8.size() == 0);
}
