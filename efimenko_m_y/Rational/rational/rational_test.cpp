#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <rational/rational.h>
#include <iostream>
TEST_CASE("testing the basics") {
    CHECK((Rational(3) == Rational(3, 1)));
    CHECK(Rational(3, 6) == Rational(1, 2));
    CHECK(Rational(1, 2) + Rational(1, 3) == Rational(5, 6));
    CHECK(Rational(3, 10) - Rational(1, 10) == Rational(1, 5));
    CHECK(Rational(-5, 3) * Rational(3, 3) == Rational(-5, 3));
    CHECK(Rational(4, 3) / Rational(-2, 3) == Rational(-2, 1));
    CHECK((Rational(4, 1) *= Rational(0, 3)) == Rational(0, 1));
    CHECK((Rational(3, 2) -= Rational(-1, 4)) == Rational(7, 4));
    CHECK((Rational(2, 9) += Rational(0, 17)) == Rational(2, 9));
    CHECK((Rational(1, 9) /= Rational(1, 9)) == Rational(1));
}
TEST_CASE(" testing rational operators") {
    CHECK(Rational(1, 2) > Rational(1, 4));
    CHECK(Rational(3, 9) < Rational(1, 2));
    CHECK(Rational(12, 13) != Rational(15, 16));
    CHECK(Rational(3, 6) <= (Rational(1, 2)));
    CHECK(Rational(2, 3) >= Rational(2, 3));
    CHECK(Rational(-1, 2) == Rational(-2, 4));
}

TEST_CASE(" testing other operators") {
    Rational a(2, 7); Rational b(1, 1);
    b = a++;
    CHECK(b == Rational(2, 7));
    CHECK(a == Rational(9, 7));
    b = a--;
    CHECK(b == Rational(9, 7));
    CHECK(a == Rational(2, 7));
    CHECK((--Rational(5, 7)) == Rational(-2, 7));
    CHECK(-Rational(100, 20) == Rational(-5));
    CHECK(+Rational(240, 40) == Rational(6));

}
TEST_CASE(" testing the exceptions") {
    CHECK_THROWS_WITH(Rational(1, 0), "Denominator must not be equal to zero");
    CHECK_THROWS_WITH((Rational(2, 3) /= Rational(0, 12)), "Division by zero");
    CHECK_THROWS_WITH((Rational(1, 6) / Rational(0, 5)), "Division by zero");
}
TEST_CASE(" testing input/ output") {
    Rational r;
    std::cin >> r;
    std::cout << r;
}