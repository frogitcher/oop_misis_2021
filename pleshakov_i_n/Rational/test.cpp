#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Rational.h"
#include <string>


TEST_CASE("Testing boolean operators") {

    Rational a(1, 2), b(-10, -20), c(3, 5),d(2, -3);

    CHECK((a == b) == true);
    CHECK((a < d) == false);
    CHECK((c > a) == true);
    CHECK((d <= c) == true);
    CHECK((a >= d) == true);
    CHECK((b != c) == true);
}

TEST_CASE("Testing arithmetic operators") {

    Rational a(1, 2), b(1, 3), e(2, 6), k(5, 2), l(-5, -2), h(2, -2), p(2, 2);

    CHECK((a+b) == Rational(5, 6));
    CHECK((a+e) == Rational(5, 6));
    CHECK((a+k) == Rational(3));
    CHECK((a+l) == Rational(3));
    CHECK((a+h) == Rational(-1, 2));
    CHECK((a-b) == Rational(1, 6));
    CHECK((a/b) == Rational(3, 2));


    CHECK((a+=b) == Rational(5, 6));
    CHECK((k*=p) == Rational(5, 2));
}

TEST_CASE("Testing unary operators") {

    Rational c(5);

    CHECK((++c) == Rational(6));
    CHECK((c++) == Rational(6));
    CHECK((--c) == Rational(6));
    CHECK((c--) == Rational(6));

}

TEST_CASE("Testing denominator") {

    Rational b(1, 2);

    CHECK_THROWS_WITH(Rational(5, 0), "denominator must not be equal to 0");
    CHECK_THROWS_WITH((b /= Rational(0, 5)), "denominator must not be equal to 0");
}



