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
    CHECK((Rational(234, 9) == Rational(25)) == false );
    CHECK((Rational(2, 7) * Rational(-5, 4) == Rational(5, 14)) == false);
    CHECK((Rational(25, 3) /= Rational(9, 3)) == Rational(25, 9));
}
TEST_CASE(" testing rational operators") {
    CHECK(Rational(1, 2) > Rational(1, 4));
    CHECK(Rational(3, 9) < Rational(1, 2));
    CHECK(Rational(12, 13) != Rational(15, 16));
    CHECK(Rational(3, 6) <= (Rational(1, 2)));
    CHECK(Rational(2, 3) >= Rational(2, 3));
    CHECK((Rational(2, 3) > Rational(2, 3)) == false);
    CHECK(Rational(78, 1) < Rational(2553, 32));  
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
    r = Rational(27, 3);
    std::ostringstream out;
    out << r;
    std::istringstream in;
    in >> r;
    CHECK(r == Rational(27, 3));
    CHECK((r == Rational(-27, 3) )== false);
    Rational t = Rational(24, 8);
    in >> t;
    CHECK((t == Rational(3)));
    CHECK((t == Rational(4, 2)) == false);
}