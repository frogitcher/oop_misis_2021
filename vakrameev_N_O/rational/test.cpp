#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.cpp"

TEST_CASE("checking different situations") {
    CHECK(Rational(0,5)==Rational(0));
    CHECK(Rational(1,2)==Rational(2,4));
    CHECK(Rational(1,2)<Rational(1,3));
    CHECK(Rational(1,3)<=Rational(1,3));
    CHECK(Rational(5)+Rational(3)==Rational(16,2));
    CHECK(Rational(5)*Rational(3,5)==Rational(3));
    CHECK(Rational(5)/Rational(5,2)==Rational(2));
    CHECK(Rational(3,2)>Rational(1));
    CHECK(Rational(3,2)!=Rational(2,3));
    CHECK(Rational(3,2)-Rational(1,2)==Rational(1));
    CHECK(Rational(2)>=Rational(2,1));
    CHECK((Rational(5, 1) += Rational(3, 1)) == Rational(8, 1));
    CHECK((Rational(5, 1) *= Rational(0, 5)) == Rational(0));
    CHECK((Rational(7, 2) -= Rational(0)) == Rational(7, 2));
    CHECK((Rational(7,2)/=Rational(2,7))==Rational(1));
}

TEST_CASE("testing exceptions"){
     CHECK_THROWS_WITH(Rational(1, 0), "Denominator must not be equal to 0!");
    CHECK_THROWS_WITH((Rational(5, 2) /= Rational(0, 3)), "Division by 0!");
}

