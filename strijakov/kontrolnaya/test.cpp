#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "kontrolnaya.h"

TEST_CASE("Testing") {
    Stack_kr stk1(1,2,3,4,5);
    Stack_kr stk2(stk1);
    CHECK(stk1 == stk2);
    CHECK(!(stk.Empty());
    CHECK(stk1.Get() == 5)
}
