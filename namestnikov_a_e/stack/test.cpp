#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack.h"

TEST_CASE("Basic functions"){
    Stack<int> st0({1,2,3,4,5});
    Stack<int> st1({1,2,3,4,5});
    Stack<int> st2({1,2,3,4,5,6});
    CHECK(st0 == st1);
    st0.Push(6);
    CHECK((st0 != st1) == true);
    st0.Pop();
    CHECK(st0 == st1);
    CHECK(st0.Get() == 5);
    CHECK((st0.Empty()) == false);
    CHECK((st0.Size()) == 5);
    st0.Swap(st2);
    CHECK((st0 != st1) == true);
    st0.Merge(st2);
    CHECK(st0.Size() == 11);
}
Stack<int> st2;
TEST_CASE("Testing exceptions") {
    CHECK_THROWS_WITH(st2.Get(), "You can't get from an empty stack");
    CHECK_THROWS_WITH(st2.Pop(), "You can't pop from an empty stack");
}