#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "rational.h"

TEST_CASE("testing arith int positive") {
    rational a = 4, b(2), c = 3, d = 6, e = 8;


    CHECK((a + b == 6) == 1);
    CHECK((a + 2 == 6) == 1);
    CHECK((rational(2) + a == 6) == 1);
    CHECK((rational(4) + 2 == 6) == 1);
    CHECK((rational(4) + 2 == d) == 1);

    CHECK((a - b == 2) == 1);
    CHECK((a - 2 == 2) == 1);
    CHECK((rational(4) - b == 2) == 1);
    CHECK((rational(4) - 2 == 2) == 1);
    CHECK((rational(4) - 2 == b) == 1);

    CHECK((a / b == 2) == 1);
    CHECK((a / 2 == 2) == 1);
    CHECK((rational(4) / b == 2) == 1);
    CHECK((rational(4) / 2 == 2) == 1);
    CHECK((rational(4) / 2 == b) == 1);

    CHECK((a * b == 8) == 1);
    CHECK((a * 2 == 8) == 1);
    CHECK((rational(4) * b == 8) == 1);
    CHECK((rational(4) * 2 == 8) == 1);
    CHECK((rational(4) * 2 == e) == 1);

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

    {
        CHECK((a++ == 4) == 1);
        CHECK((a == 5) == 1);
        CHECK((++a == 6) == 1);
        a = 4;
    }
    {
        CHECK((a-- == 4) == 1);
        CHECK((a == 3) == 1);
        CHECK((--a == 2) == 1);
        a = 4;
    }
}

TEST_CASE("testing arith double positive") {
    rational a(13, 3), b(11, 3), c(1, 3), d (4, 3), e (1, 4), f (14, 3), g (2, 3), h = 13;


    CHECK((a + c == rational(14, 3)) == 1);
    CHECK((a + rational(1, 3) == rational(14, 3)) == 1);
    CHECK((rational(13, 3) + c == rational(14, 3)) == 1);
    CHECK((rational(13, 3) + rational(1, 3) == rational(14, 3)) == 1);
    CHECK((rational(13, 3) + rational(1, 3) == f) == 1);

    CHECK((a - b == rational(2, 3)) == 1);
    CHECK((a - rational(11, 3) == rational(2, 3)) == 1);
    CHECK((rational(13, 3) - b == rational(2, 3)) == 1);
    CHECK((rational(13, 3) - rational(11, 3) == rational(2, 3)) == 1);
    CHECK((rational(13, 3) - rational(11, 3) == g) == 1);

    CHECK((a / c == rational(13)) == 1);
    CHECK((a / rational(1, 3) == rational(13)) == 1);
    CHECK((rational(13, 3) / c == rational(13)) == 1);
    CHECK((rational(13, 3) / rational(1, 3) == rational(13)) == 1);
    CHECK((rational(13, 3) / rational(1, 3) == h) == 1);

    CHECK((d * e == rational(1, 3)) == 1);
    CHECK((d * rational(1, 4) == rational(1, 3)) == 1);
    CHECK((rational(4, 3) * e == rational(1, 3)) == 1);
    CHECK((rational(4, 3) * rational(1, 4) == rational(1, 3)) == 1);
    CHECK((rational(4, 3) * rational(1, 4) == c) == 1);

    {
        a += c;
        CHECK((a == rational(14, 3)) == 1);
        a = rational(13, 3);
        a += rational(1, 3);
        CHECK((a == rational(14, 3)) == 1);
        a = rational(13, 3);
    }
    {
        a -= b;
        CHECK((a == rational(2, 3)) == 1);
        a = rational(13, 3);
        a -= rational(11, 3);
        CHECK((a == rational(2, 3)) == 1);
        a = rational(13, 3);
    }
    {
        a /= c;
        CHECK((a == 13) == 1);
        a = rational(13, 3);
        a /= rational(1, 3);
        CHECK((a == 13) == 1);
        a = rational(13, 3);
    }
    {
        d *= e;
        CHECK((d == rational(1, 3)) == 1);
        d = rational(4, 3);
        d *= rational(1, 4);
        CHECK((d == rational(1, 3)) == 1);
        d = rational(4, 3);
    }

    {
        CHECK((a++ == rational(13, 3)) == 1);
        CHECK((a == rational(16, 3)) == 1);
        CHECK((++a == rational(19, 3)) == 1);
        a = rational(13, 3);
    }
    {
        CHECK((a-- == rational(13, 3)) == 1);
        CHECK((a == rational(10, 3)) == 1);
        CHECK((--a == rational(7, 3)) == 1);
        a = rational(13, 3);
    }
}

TEST_CASE("testing arith negative") {
    rational a(-13, 3), b(11, -3), c(1, -3), d (-4, 3), e (1, -4), f (14, -3), g (-2, 3), h = -13;


    CHECK((a + c == rational(-14, 3)) == 1);
    CHECK((a + rational(-1, 3) == rational(14, -3)) == 1);
    CHECK((rational(-13, 3) + c == rational(-14, 3)) == 1);
    CHECK((rational(13, -3) + rational(1, -3) == rational(-14, 3)) == 1);
    CHECK((rational(-13, 3) + rational(-1, 3) == f) == 1);

    CHECK((a - b == rational(-2, 3)) == 1);
    CHECK((a - rational(-11, 3) == rational(-2, 3)) == 1);
    CHECK((rational(-13, 3) - b == rational(2, -3)) == 1);
    CHECK((rational(13, -3) - rational(11, -3) == rational(-2, 3)) == 1);
    CHECK((rational(-13, 3) - rational(-11, 3) == g) == 1);

    CHECK((a / c == rational(13)) == 1);
    CHECK((a / rational(-1, -3) == rational(-13)) == 1);
    CHECK((rational(-13, -3) / c == rational(-13)) == 1);
    CHECK((rational(13, -3) / rational(1, -3) == rational(13)) == 1);
    CHECK((rational(13, 3) / rational(-1, 3) == h) == 1);

    CHECK((d * e == rational(1, 3)) == 1);
    CHECK((d * rational(-1, -4) == rational(1, -3)) == 1);
    CHECK((rational(-4, 3) * e == rational(1, 3)) == 1);
    CHECK((rational(-4, 3) * rational(1, 4) == rational(1, -3)) == 1);
    CHECK((rational(4, 3) * rational(-1, 4) == c) == 1);

    {
        a += c;
        CHECK((a == rational(14, -3)) == 1);
        a = rational(-13, 3);
        a += rational(-1, 3);
        CHECK((a == rational(14, -3)) == 1);
        a = rational(-13, 3);
    }
    {
        a -= b;
        CHECK((a == rational(-2, 3)) == 1);
        a = rational(-13, 3);
        a -= rational(11, -3);
        CHECK((a == rational(-2, 3)) == 1);
        a = rational(13, -3);
    }
    {
        a /= c;
        CHECK((a == 13) == 1);
        a = rational(-13, 3);
        a /= rational(1, 3);
        CHECK((a == -13) == 1);
        a = rational(-13, 3);
    }
    {
        d *= e;
        CHECK((d == rational(1, 3)) == 1);
        d = rational(-4, 3);
        d *= rational(1, 4);
        CHECK((d == rational(-1, 3)) == 1);
        d = rational(4, -3);
    }
}

TEST_CASE("testing comparison") {
    rational a = 5023, b(5023, 254), c = 345, d(1000, 2);


    CHECK((rational(5023) == rational(5023)) == 1);
    CHECK((rational(5024) == rational(5023)) == 0);
    CHECK((rational(5023, 254) == rational(5023,254)) == 1);
    CHECK((rational(10046, 508) == rational(10046, 508)) == 1);
    CHECK((rational(5024, 254) == rational(5023,254)) == 0);
    CHECK((rational(10, 2) == rational(50, 10)) == 1);

    CHECK((a == rational(5023)) == 1);
    CHECK((rational(5023) == a) == 1);
    CHECK((a == a) == 1);
    CHECK((a == rational(5024)) == 0);

    CHECK((b == rational(5023, 254)) == 1);
    CHECK((rational(5023, 254) == b) == 1);
    CHECK((b == b) == 1);
    CHECK((b == rational(5024, 254)) == 0);

    CHECK((rational(5023) != rational(5023)) == 0);
    CHECK((rational(5024) != rational(5023)) == 1);
    CHECK((rational(5023, 254) != rational(5023, 254)) == 0);
    CHECK((rational(10046, 508) != rational(10046, 508)) == 0);
    CHECK((rational(5024, 254) != rational(5023, 254)) == 1);

    CHECK((a != c) == 1);
    CHECK((a + c != a) == 1);

    CHECK((rational(5024) > rational(5023)) == 1);
    CHECK((rational(5024) >= rational(5023)) == 1);
    CHECK((rational(5024) >= rational(5024)) == 1);
    CHECK((rational(5023) < rational(5024)) == 1);
    CHECK((rational(5023) <= rational(5024)) == 1);
    CHECK((rational(5023) <= rational(5023)) == 1);

    CHECK((rational(5023) > rational(5024)) == 0);
    CHECK((rational(5023) >= rational(5024)) == 0);
    CHECK((rational(5024) > rational(5024)) == 0);
    CHECK((rational(5024) < rational(5023)) == 0);
    CHECK((rational(5024) <= rational(5023)) == 0);
    CHECK((rational(5023) < rational(5023)) == 0);

    CHECK((rational(-5024) == rational(-5024)) == 1);
    CHECK((rational(-5024) > rational(5023)) == 0);
    CHECK((rational(-5024) > rational(-5023)) == 0);
    CHECK((rational(-5024) < rational(-5023)) == 1);
    CHECK((rational(-5023) > rational(-5024)) == 1);

    CHECK((a > c) == 1);
    CHECK((a > rational(150)) == 1);
    CHECK((b < d) == 1);
    CHECK((b < rational(1000, 2)) == 1);
}