#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "rational.h"

TEST_CASE("testing arith int positive") {
    rational a = 4, b(2), c = 3;


    CHECK((a + b == 6) == 1);
    CHECK((a + 2 == 6) == 1);
    //CHECK((2 + a == 6) == 1);
    CHECK(((rational)4 + 2 == 6) == 1);

    CHECK((a - b == 2) == 1);
    CHECK((a - 2 == 2) == 1);
    //CHECK((4 - b == 2) == 1);
    CHECK(((rational)4 - 2 == 2) == 1);

    CHECK((a / b == 2) == 1);
    CHECK((a / 2 == 2) == 1);
    //CHECK((4 / b == 2) == 1);
    CHECK(((rational)4 / 2 == 2) == 1);

    CHECK((a * b == 8) == 1);
    CHECK((a * 2 == 8) == 1);
    //CHECK((4 * b == 8) == 1);
    CHECK(((rational)4 * 2 == 8) == 1);

    {
    a += b;
    CHECK((a == 6) == 1);
    a = 4;
    a += 2;
    CHECK((a == 6) == 1);
    a = 4;
    }
    {
    a -= b;
    CHECK((a == 2) == 1);
    a = 4;
    a -= 2;
    CHECK((a == 2) == 1);
    a = 4;
    }
    {
    a /= b;
    CHECK((a == 2) == 1);
    a = 4;
    a /= 2;
    CHECK((a == 2) == 1);
    a = 4;
    }
    {
    a *= b;
    CHECK((a == 8) == 1);
    a = 4;
    a *= 2;
    CHECK((a == 8) == 1);
    a = 4;
    }
}


TEST_CASE("testing arith double positive") {
    rational a(13, 3), b(11, 3), c(1, 3), d = (4, 3), e = (1, 4), f = 2;


    CHECK((a + c == 4.66) == 1);
    CHECK((a + 0.33 == 4.66) == 1);
    //CHECK((4.33 + c == 4.66) == 1);
    CHECK(((rational)4.33 + 0.33 == 4.66) == 1);

    CHECK((a - b == 0.66) == 1);
    CHECK((a - 3.66 == 0.66) == 1);
    //CHECK((4.33 - b == 0.66) == 1);
    CHECK(((rational)4.33 - 3.66 == 0.66) == 1);

    CHECK((a / c == 13) == 1);
    CHECK((a / 0.33 == 13) == 1);
    //CHECK((4.33 / c == 13) == 1);
    CHECK(((rational)4.33 / 0.33 == 13) == 1);

    CHECK((d * e == 0.33) == 1);
    CHECK((d * 0.25 == 0.33) == 1);
    //CHECK((1.33 * e == 0.33) == 1);
    CHECK(((rational)1.33 * 0.25 == 0.33) == 1);

    {
        a += c;
        CHECK((a == 4.66) == 1);
        a = 4.33;
        a += 0.33;
        CHECK((a == 4.66) == 1);
        a = 4.33;
    }
    {
        a -= b;
        CHECK((a == 0.66) == 1);
        a = 4.33;
        a -= 3.66;
        CHECK((a == 0.66) == 1);
        a = 4.33;
    }
    {
        a /= c;
        CHECK((a == 13) == 1);
        a = 4.33;
        a /= 0.33;
        CHECK((a == 13) == 1);
        a = 4.33;
    }
    {
        d *= e;
        CHECK((d == 0.33) == 1);
        d = 1.33;
        d *= 0.25;
        CHECK((d == 0.33) == 1);
        d = 1.33;
    }
}


TEST_CASE("testing arith negative") {

}

TEST_CASE("testing comparison") {

}