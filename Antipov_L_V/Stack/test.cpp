#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "stack.h"

TEST_CASE("Testing initialization and methods.") {
    Stack<int> a;
    CHECK(a.Size() == 0);
    CHECK(a.Empty());

    Stack<int> b0{1, 2, 3, 4, 5};
    for (int i = 5; i > 0; i--) {
        CHECK(b0.Get() == i);
        b0.Pop();
    }

    Stack<int> b1{1};
    b1.Pop();
    CHECK(b1.Size() == 0);

    Stack<int> b2{1, 2, 3, 4, 5};
    b2.Clear();
    CHECK(b2.Size() == 0);


    Stack<int> b3;
    for (int i = 1; i <= 5; i++) {
        b3.Push(i);
        CHECK(b3.Get() == i);
    }

    Stack<int> c1;
    Stack<int> c2{1, 2, 3, 4, 5};
    Stack<int> c_temp(c2);
    c1.Swap(c2);
    for (int i = 5; i > 0; i--) {
        CHECK(c1.Get() == c_temp.Get());
        c1.Pop();
        c_temp.Pop();
    }


    Stack<int> d1{1, 2, 3, 4, 5};
    Stack<int> d2{6, 7, 8};

    d1.Merge(d2);

    CHECK(d1.Size() == 8);
    for (int i = 8; i > 0; i--) {
        CHECK(d1.Get() == i);
        d1.Pop();
    }
}


TEST_CASE("Testing operators") {
    Stack<int> a{1, 2, 3, 4, 5};
    Stack<int> b{5, 4, 3, 2, 1};
    Stack<int> c0;
    Stack<int> c1;
    CHECK(a != b);
    b = a;
    CHECK(a == b);

    CHECK(c0 == c1);
}

TEST_CASE("Testing exceptions") {
    Stack<int> a;
    CHECK_THROWS_WITH(a.Get(), "Stack is empty.");
    CHECK_THROWS_WITH(a.Pop(), "Stack is empty.");
}
