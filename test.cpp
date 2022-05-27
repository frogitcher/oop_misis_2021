#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "myStack.h"
#include <string>
#include <iostream>

TEST_CASE("just testing") {

    myStack<int> st1;
    myStack<int> st2;
    myStack<int> st3 = st1;
    CHECK(st1 == st3);

    myStack<int> st4{ 1,2,3,4 };
    CHECK(st4.getSize() == 4);
    CHECK(st4 != st1);

    myStack<int> st5(st4);

    st1.push(5);
    CHECK(st1.get() == 5);

    st2.push(1);
    st2.pop();
    CHECK(st2.empty());

    st4.clear();
    CHECK(st4.empty());

    myStack<int> st6{ 1,2,3 };
    myStack<int> st7{ 4,5 };
    st7.merge(st6);
    CHECK(st7.get() == 5);

    myStack<int> stBad;
    CHECK_THROWS_WITH(stBad.get(), "Empty stack");
    CHECK_THROWS_WITH(stBad.pop(), "Empty stack");
}