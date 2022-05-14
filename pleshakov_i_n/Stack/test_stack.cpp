#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <string>

#include "doctest.h"
#include "stack.h"


TEST_CASE ("testing Constructors, Pop, Push, Size, ==, ="){
    Stack<int> a, b({1, 3, 2, 4}), c(b), e({9, 6, 3});
    Stack<int> d = Stack<int>({9, 6, 3});

    CHECK(d == e);
    CHECK(c == b);

    a.Push(5);
    a.Push(10);

    CHECK(a.Size() == 2);

    a.Pop();
    CHECK(a.Size() == 1);

    a.Pop();
    CHECK_THROWS_WITH(a.Pop(), "Stack is empty");

    e = b;
    CHECK(e == Stack<int>({1, 3, 2, 4}));

    e.Push(-1);
    e.Push(-2);
    for (int i=0; i<6; ++i){
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

TEST_CASE ("testing Empty, Get, Swap"){
    Stack<int> a, b({1, 3, 2, 4}), c(b), e({9, 6, 3});
    b.Swap(e);

    CHECK(a.Empty());
    CHECK(b == Stack<int>({9, 6, 3}));
    CHECK(b != Stack<int>({1, 3, 2, 4}));
    CHECK_FALSE(b. Empty());

    CHECK(b.Get() == 3);
    CHECK(b.Size() == 3);
    CHECK(e.Get() == 4);
    CHECK(e.Size() == 4);

    CHECK_THROWS_WITH(a.Get(), "Stack is empty");

    c.Swap(a);
    CHECK(c.Size() == 0);
    CHECK(a.Get() == 4);
    CHECK(a.Size() == 4);
}

TEST_CASE ("Testing Merge, Clear"){
    Stack<int> a({1, 3, 2, 4}), b, c(a), d;
    b = Stack<int>({5, 6, 7});

    d.Merge(a);

    CHECK(d == c);
    CHECK(a.Size() == 4);
    CHECK(d.Size() == 4);

    d.Merge(b);

    CHECK(d == Stack<int>({1, 3, 2, 4, 5, 6, 7}));
    CHECK(d.Size() == 7);
    CHECK(b.Size() == 3);
    CHECK(d.Get() == 7);

    d.Clear();
    CHECK(d.Size() == 0);
    CHECK_THROWS_WITH(d.Get(), "Stack is empty");

    c.Clear();
    c.Merge(d);

    CHECK(c.Size() == 0);
    CHECK_THROWS_WITH(d.Get(), "Stack is empty");
}

TEST_CASE ("Testing templates"){
    Stack<double> d({1.5, 1.9, 2, 1.231});
    Stack<std::string> s({"string1", "string2", "string3"});
    Stack<unsigned int> i;
    i.Push(111);
    i.Push(12771);
    i.Push(1);

    CHECK(d.Get() == 1.231);
    CHECK(s.Get() == "string3");
    CHECK(i.Get() == 1);

    CHECK(d.Size() == 4);
    CHECK(s.Size() == 3);
    CHECK(i.Size() == 3);

    d.Pop();
    s.Pop();
    i.Pop();

    CHECK(d.Get() == 2);
    CHECK(s.Get() == "string2");
    CHECK(i.Get() == 12771);

    d.Clear();
    s.Clear();
    i.Clear();

    CHECK(d.Size() == 0);
    CHECK(s.Size() == 0);
    CHECK(i.Size() == 0);

}
