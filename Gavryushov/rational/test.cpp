#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

TEST_CASE("Constructor") 
{
    CHECK(Rational() == Rational(0,1));
    CHECK(Rational(7,35) == Rational(1,5));
    CHECK(Rational(5, -10) == Rational(-1, 2));
    CHECK(Rational(5,5)== Rational(1));
    CHECK(Rational(-3,1)==Rational(-3));
    CHECK_THROWS_WITH(Rational(1, 0), "denominator must not be equal to 0");
}

TEST_CASE("Operators"){
    CHECK(++Rational(5,4) == Rational(9,4));
    CHECK(--Rational(5,4)==Rational(2,8));
    Rational c = Rational(4,-2);
    Rational b=c++;
    CHECK(c==Rational(1,-1));
    CHECK (b==Rational(-2));
    CHECK((Rational(4,3)+Rational(3,5)) == Rational(29,15));
    c += Rational(-1);
    CHECK(c==Rational(4,-2));
    CHECK((Rational(1,10)-Rational(1,2))==Rational(2,-5));
    CHECK((Rational(4,3)*Rational(1,4))==Rational(1,3));
    CHECK((Rational(4,3)/Rational(1,4))==Rational(16,3));
    c*=Rational(4);
    CHECK(c==Rational(-8));
    c/=Rational(-2);
    CHECK(c==Rational(4));
    c-=2;
    CHECK(c==Rational(2,1));
    b=c--;
    CHECK(c==Rational(1));
    CHECK(b==Rational(2));
    CHECK_THROWS_WITH(Rational(3,2)/Rational(0,5),"Dividing by zero is impossible");
    CHECK_THROWS_WITH(Rational(3,2)/=Rational(0,5),"Dividing by zero is impossible");
    CHECK((+Rational(3,2)) == Rational(6,4));
    CHECK((-Rational(-3,2)) == Rational(6,4));
}

TEST_CASE("bools"){
    CHECK(Rational(5,4)==Rational(25,20));
    CHECK(Rational(10,9)<Rational(10,8));
    CHECK(Rational(10,9)<=Rational(50,45));
    CHECK(Rational(10,9)>Rational(10,10));
    CHECK(Rational(10,9)>=Rational(50,45));
    CHECK(Rational(5,4)!=Rational(-5,4));
    
}

TEST_CASE("output"){
     std::ostringstream out;
     Rational a(-5,-30);
     out << a;
     CHECK(out.str() == "1/6");
}