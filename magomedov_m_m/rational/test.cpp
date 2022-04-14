#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

TEST_CASE("Booleans") {
    Rational a(1, 2), b(-3, 4), c, d(1), f(5, 10);
    CHECK((a != b));
    CHECK((a == f));
    CHECK((a >= b));
    CHECK((c <= d));
    CHECK(!(a > f));
    CHECK((b < d));
}

TEST_CASE("+ - * / += *= -= /=") {
    Rational a(1, 2), b(-3, 4), c, d(1), f(5, 10);
    CHECK((a+b == Rational(-1,4)));
    CHECK((a-b == Rational(5,4)));
    CHECK((a * d==a));
    CHECK((f / a==Rational(1)));
    a += b;
    c -= d;
    f *= a;
    b /= d;
    CHECK((a == Rational(-1, 4)));
    CHECK((c == Rational(-1)));
    CHECK((f == Rational(-1,8)));
    CHECK((b == Rational(-3,4)));
}

TEST_CASE("++ --") {
    Rational a(1, 2), b(-3, 4), c, d(1), f(5, 10);
    CHECK(!(Rational (1,2)== ++a));
    CHECK((Rational (3,2)== a));
    CHECK((Rational (-3,4) == b++));
    CHECK((Rational (1,4) == b));
    CHECK((Rational () == --d));
    CHECK((Rational (5,10)==  f--));
    CHECK((Rational (-5,10)==  f));
}

TEST_CASE("Errors") {
    Rational a(0,1);
    CHECK_THROWS_WITH(Rational(1, 0), "You cannot divide by zero");
    CHECK_THROWS_WITH(Rational(1) /= a, "You cannot divide by zero");
}
 
