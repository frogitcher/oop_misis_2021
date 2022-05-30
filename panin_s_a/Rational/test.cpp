#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Rational.h"
#include <string>
#include <iostream>
using namespace std;

TEST_CASE("Testing boolean operators") {

    Rational r1(7, 30), r2(7, 29), r3(15,30), r4(0), r5(1,2), r6(25,129), r7(24,121);
    CHECK((r1 < r2) == true);
    CHECK((r1 < r3) == true);
    CHECK((r1 > r4) == true);
    CHECK((r3 == r5) == true);
    CHECK((r1 != r2) == true);
    CHECK((r6 <= r7) == true);

    Rational a(1, 2), b(-10, -20), c(3, 5),d(2, -3);
    CHECK((a == b) == true);
    CHECK((a < d) == false);
    CHECK((c > a) == true);
    CHECK((d <= c) == true);
    CHECK((a >= d) == true);
    CHECK((b != c) == true);
}

TEST_CASE("Testing arithmetic operators") {

    Rational r1(7,3), r2(10, 7), r3(1,2), r4(-1,2), r5(-10), r6(5);

    CHECK((r1 + r2) == Rational(79, 21));
    CHECK((r3 + r4) == Rational(0));
    CHECK((r5 + r6) == Rational(-5));
    CHECK((r1 + r3) == Rational(17, 6));
    CHECK((r1 + r4) == Rational(11,6));
    CHECK((r1 + r5) == Rational(23,-3));


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

    Rational c(10);

    CHECK((++c) == Rational(11));
    CHECK((c++) == Rational(11));
    CHECK((--c) == Rational(11));
    CHECK((c--) == Rational(11));

    Rational r(3,2);

    CHECK((++r) == Rational(5,2));
    r = Rational(3,2);
    CHECK((r++) == Rational(3,2));
    r = Rational(0);
    CHECK((--r) == Rational(-1));
}

TEST_CASE("Testing denominator") {

    Rational b(3, 7);
    CHECK_THROWS_WITH(Rational(0, 0), "denominator must not be equal to zero");
    CHECK_THROWS_WITH(Rational(7, 0), "denominator must not be equal to zero");
    CHECK_THROWS_WITH((b /= Rational(0, 7)), "denominator must not be equal to zero");
}
