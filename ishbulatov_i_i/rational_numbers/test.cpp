#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"
TEST_CASE("test two")
{
    rational a=rational(14,3);
    rational b=rational(20,2);
    rational c=rational(3,2);
    rational d=rational(8,11);
    CHECK((a++)==rational(17,3));
    CHECK((b--)==rational(9,1));
}
TEST_CASE("test arifm") {
    rational a=rational(5,2);
    rational b=rational(7,4);
    rational c=rational(19,4);
    rational d=rational(33,12);
    CHECK(a+b==rational(17,4));
    CHECK(d-a==rational(3,12));
    CHECK(b*a==rational(35,8));
    CHECK((a+=b)==rational(17,4));
    CHECK((d-=a)==rational(3,12));
    CHECK((a*=b)==rational(35,8));
}
TEST_CASE("test boolean")
{
   rational a=rational(5,2);
    rational b=rational(7,4);
    rational c=rational(19,4);
    rational d=rational(33,12);
    CHECK((a>b)==1);
    CHECK((a>3)==0);
    CHECK((a<b)==0);
    CHECK((a<10)==1);
    CHECK((a==b)==0);
    CHECK((a==rational(5,2))==1);
    CHECK((a>=b)==1);
    CHECK((a>=rational(4,2))==1);
    CHECK((a<=b)==0);
    CHECK((d<=rational(7,3))==1);
    CHECK((a!=b)==1);
    CHECK((a!=rational(5,2))==0);
}
TEST_CASE("test exceptions")
{
    CHECK_THROWS_WITH(rational(133, 0), "denominator must not be equal to 0");
}
