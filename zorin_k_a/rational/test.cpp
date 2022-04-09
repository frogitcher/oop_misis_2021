#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"


TEST_CASE("testing the ==") {
    Rational a=Rational(5,3);
    Rational b=Rational(7,4);
    Rational c=Rational(17,2);
    Rational d=Rational(33,12);
    CHECK(a+b==Rational(41,12));
    CHECK(d-a==Rational(1,12));
    CHECK(b*a==Rational(35,12));

    CHECK((a+=b)==Rational(41,12));
    CHECK((d-=a)==Rational(1,12));
    CHECK((a*=b)==Rational(35,12));
}
TEST_CASE("boolean things")
{
   Rational a=Rational(11,3);
    Rational b=Rational(15,5);
    Rational c=Rational(3,1);
    Rational d=Rational(7,11);
    CHECK((a>b)==1);
    CHECK((a>3)==1);
    CHECK((a<b)==0);
    CHECK((a<10)==1);
    CHECK((a==b)==0);
    CHECK((a==Rational(33,9))==1);
    CHECK((a>=b)==1);
    CHECK((a>=Rational(33,9))==1);
    CHECK((a<=b)==0);
    CHECK((d<=Rational(7,11))==1);
    CHECK((a!=b)==1);
    CHECK((a!=Rational(11,3))==0);
}
TEST_CASE("other stuff")
{
     Rational a=Rational(11,3);
    Rational b=Rational(15,5);
    Rational c=Rational(3,1);
    Rational d=Rational(7,11);
    CHECK((a++)==Rational(14,3));
     CHECK((b--)==Rational(2,1));
}
TEST_CASE("exceptions")
{
    CHECK_THROWS_WITH(Rational(228, 0), "denominator must not be equal to 0");
}
