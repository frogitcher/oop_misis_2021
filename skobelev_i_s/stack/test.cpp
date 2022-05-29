#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack.h"

TEST_CASE("checking results") {
    Stack<long long> one {1, 3 ,6};
    Stack<long long> two {4, 7, 9, 10};
    CHECK(one.Size() == 3);
    CHECK(two.Size() == 4);
    two.Pop();
    CHECK(two.Size() == 3);
    CHECK(one != two);
    two.Clear();
    CHECK(two.Size() == 0);
    two.Push(1);
    CHECK(two.Size() == 1);
    Stack<long long> three = one;
    CHECK(one == three);
    one.Merge(three);
    CHECK(one.Size() == 6);
}
