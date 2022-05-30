#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "stack.h"

TEST_CASE("Basic functionality") {
    Stack<int> s1;
    Stack<int> s2({1, 2, 3, 4});
    Stack<int> s3(s2);

    CHECK_THROWS_WITH(s1.pop(), "Stack is empty");

    CHECK(s2.pop() == 4);
    CHECK(s2.pop() == 3);
    CHECK(s2.getSize() == 2);
    s2.push(3);
    CHECK(s2.getValue() == 3);
    CHECK(s2.getSize() == 3);

    CHECK(s3.getValue() == 4);
    CHECK(s3.getSize() == 4);

    s2.swap(s3);
    CHECK(s2.pop() == 4);
    CHECK(s2.getSize() == 3);

    s1.merge(s2);
    s1.merge(s3);
    CHECK(s1.getValue() == 3);
    CHECK(s1.getSize() == 6);
}

TEST_CASE("Bool operations") {
    Stack<int> s1({1, 2, 3});
    Stack<int> s2({1, 2, 3});

    CHECK(s1 == s2);
    s1.pop();
    CHECK(s1 != s2);
}