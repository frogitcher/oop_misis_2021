#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "RationalNumber.h"


TEST_CASE("Exceptions"){
    CHECK_THROWS_WITH(RationalNumber(1, 0), "Denominator is equal to 0");
    CHECK_THROWS_WITH((RationalNumber(1, 1) /= RationalNumber(0, 1)), "division by 0");
}
TEST_CASE("Output"){
    std::stringstream teststream;
    teststream << RationalNumber(1, 2);
    CHECK(teststream.str() == "1/2");
}

TEST_CASE("Arithmetic"){
    CHECK(RationalNumber(100, 1000) == RationalNumber(1, 10));
    CHECK(RationalNumber(1, 2) + RationalNumber(1, 2) == RationalNumber(1, 1));
    CHECK(RationalNumber(3, 3) - RationalNumber(1, 2) == RationalNumber(2, 4));
    CHECK(RationalNumber(2, 5) * RationalNumber(1, 2) == RationalNumber(2, 10));
    CHECK(RationalNumber(5, 1) / RationalNumber(1, 2) == RationalNumber(10, 1));

    CHECK((RationalNumber(5, 1) += RationalNumber(3, 1)) == RationalNumber(8, 1));
    CHECK((RationalNumber(5, 1) *= RationalNumber(0, 5)) == RationalNumber(0));
    CHECK((RationalNumber(7, 2) -= RationalNumber(0, 5723)) == RationalNumber(7, 2));
    CHECK((RationalNumber(8, 2) /= RationalNumber(1, 2)) == RationalNumber(8, 1));
}

TEST_CASE("boolean"){
    CHECK(!(RationalNumber(10, 1) == RationalNumber(9, 1)));
    CHECK(!(RationalNumber(10, 5) == RationalNumber(12, 4)));

}