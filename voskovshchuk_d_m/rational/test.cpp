#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "rational.h"

TEST_CASE("testing int") {
    rational a = 1.4, b = -2, c = 0.666, d(-1.33);
    CHECK((a + b == -0.6) == 1);
    CHECK((b + c == -1.33) == 1);
    CHECK((c + 0.333 == 1) == 1);
}
