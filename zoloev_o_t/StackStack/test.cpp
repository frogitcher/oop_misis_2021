#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <string>

#include "doctest.h"
#include "StackHeader.h"


TEST_CASE("testing Constructors, Pop, Push, Size, ==, =") {
    Stack<int> a;
    Stack<int> b({1, 3, 2, 4});
    Stack<int> c(b);
    Stack<int> e({9, 6, 3});
    Stack<int> d = Stack<int>({9, 6, 3});

    CHECK(d == e);
    CHECK(c == b);

    a.Push(5);
    a.Push(10);

    CHECK(a.Size() == 2);

    a.Pop();
    CHECK(a.Size() == 1);
    a.Pop();
    CHECK_THROWS_WITH(a.Pop(), "Stack is empty!");

    e = b;
    CHECK(e == Stack<int>({1, 3, 2, 4}));

    e.Push(-1);
    e.Push(-2);

    for (int i = 0; i < 6; ++i) {
        CHECK(e.Size() == 6 - i);
        e.Pop();
    }

   CHECK(e.Size() == 0);
    CHECK(a.Size() == 0);
    CHECK(a.Size() == e.Size());
  CHECK(a == e);
    CHECK_FALSE(e == Stack<int>({1}));

    b = a;
    CHECK(b.Size() == 0);
}

TEST_CASE("testing Empty, GetHead, Swap") {
    Stack<int> a, b({1, 3, 2, 4}), c(b), e({9, 6, 3});
    b.Swap(e);

    CHECK(a.Empty());
    CHECK(b == Stack<int>({9, 6, 3}));
    CHECK(b != Stack<int>({1, 3, 2, 4}));
    CHECK_FALSE(b. Empty());

    CHECK(b.GetHead() == 3);
    CHECK(b.Size() == 3);
    CHECK(e.GetHead() == 4);
    CHECK(e.Size() == 4);

    CHECK_THROWS_WITH(a.GetHead(), "Stack is empty!");

    c.Swap(a);
    CHECK(c.Size() == 0);
    CHECK(a.GetHead() == 4);
    CHECK(a.Size() == 4);
}


TEST_CASE("Testing Merge, Clear") {
//
    Stack<int> a({1, 2, 3, 4, 5});
    Stack<int> d {1, 2, 3};
	a.Merge(d);
	CHECK(a.Size() == 8);
	CHECK(d.Size() == 0);
	a.Clear();
	CHECK(a.Size() == 0);


}

TEST_CASE("Testing templates") {
    Stack<double> dbl({1.7, 1.8, 1, 1.9});
    Stack<std::string> stack_string({"s1", "s2", "s3"});

    CHECK(dbl.GetHead() == 1.9);
    CHECK(stack_string.GetHead() == "s3");
    CHECK(dbl.Size() == 4);
    CHECK(stack_string.Size() == 3);

    dbl.Pop();
    stack_string.Pop();

    CHECK(dbl.GetHead() == 1);
    CHECK(stack_string.GetHead() == "s2");
    dbl.Clear();
    stack_string.Clear();
    CHECK(dbl.Size() == 0);
    CHECK(stack_string.Size() == 0);
}
