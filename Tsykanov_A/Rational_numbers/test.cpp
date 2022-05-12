#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Rational_numbers.h"
#include "doctest.h"
#include <string>
#include <sstream>
#include <iostream>
TEST_CASE("Testing constructors."){
    CHECK(Rational(5) == Rational(5, 1));
    Rational a = Rational(5, 1);
    CHECK(a == Rational(5));
}
TEST_CASE("Testing compare."){
    CHECK(Rational(3, 2) < Rational(5, 2));
    CHECK(Rational(3, 2) <= Rational(4, 2));
    CHECK(Rational(3, 2) <= Rational(3, 2));
    CHECK(Rational(13, 3) > Rational(9, 4));
    CHECK(Rational(45, 25) >= Rational(9, 5));
    CHECK(Rational(45, 25) == Rational(9, 5));
    CHECK_FALSE(Rational(43, 25) == Rational(9, 5));
    CHECK_FALSE(Rational(43, 25) >= Rational(9, 5));
    CHECK_FALSE(Rational(48, 25) <= Rational(9, 5));
    CHECK_FALSE(Rational(45, 25) < Rational(9, 5));
    CHECK_FALSE(Rational(45, 25) > Rational(9, 5));
}
TEST_CASE("Testing arithmetic operations") {
    CHECK(Rational(200, 2000) == Rational(1, 10));
    CHECK(Rational(1, 2) + Rational(1, 2) == Rational(1, 1));
    CHECK(Rational(3, 3) - Rational(1, 2) == Rational(2, 4));
    CHECK(Rational(1, 3) - Rational(5, 3) == Rational(-4, 3));
    CHECK(Rational(2, 5) * Rational(1, 2) == Rational(2, 10));
    CHECK(Rational(5, 1) / Rational(1, 2) == Rational(10, 1));
    CHECK(Rational(4, 3) / Rational(-3, 4) == Rational(-16, 9));
    CHECK((Rational(5, 1) += Rational(3, 1)) == Rational(8, 1));
    CHECK((Rational(5, 1) *= Rational(0, 199)) == Rational(0));
    CHECK((Rational(7, 2) -= Rational(0, 7895)) == Rational(7, 2));
    CHECK((Rational(8, 2) /= Rational(1, 2)) == Rational(8, 1));
}
TEST_CASE("Testing boolean functions") {
    CHECK(Rational(1, -1) == Rational(-1, 1));
    CHECK(Rational(-1, 1) != Rational(1, 1));
    CHECK(Rational(20, 1) > Rational(1, 20));
    CHECK(Rational(-6, 9) < (Rational(5, -9)));
    CHECK(Rational(4, 7) >= (Rational(7, 31)));
    CHECK(Rational(4, 7) >= (Rational(4, 7)));
    CHECK(Rational(3, 14) <= (Rational(7, 15)));
    CHECK(Rational(3, 14) <= (Rational(3, 14)));
}
TEST_CASE("Testing other stuff") {
    std::stringstream str;
    std::stringstream str2;
    str << "3/4";
    str2 << Rational(3,4);
    CHECK(str.str() == str2.str());
    CHECK(-Rational(250, 50) == Rational(-5));
    CHECK(+Rational(450, 50) == Rational(9));
    CHECK(++Rational(1, 2) == Rational(3, 2));
    CHECK((--Rational(3, 5)) == Rational(-2, 5));
    Rational a(3, 5);
    CHECK(((a++) == Rational(3, 5)));
    CHECK(a == Rational(8, 5));
    Rational b(2, 5);
    CHECK(((b--) == Rational(2, 5)));
    CHECK(b == Rational(-3, 5));
}
TEST_CASE("Testing exceptions") {
    CHECK_THROWS_WITH(Rational(1, 0), "Denominator must not be equal to 0!");
    CHECK_THROWS_WITH((Rational(4, 9) /= Rational(0, 23)), "Division by 0!");
}