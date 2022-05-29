#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

TEST_CASE("Constructor") 
{
   CHECK (Rational()==Rational(0,1));
   CHECK (Rational(1)==Rational(1,1));
   CHECK (Rational(-5)==Rational(-5,1));
   CHECK (Rational(6,-5)==Rational(-6,5));
   CHECK (!(Rational(0,-1)==Rational(-1,1)));
   CHECK (Rational(-800, -100)==Rational(8, 1));
   CHECK (!(Rational(80,-10)==Rational(-8,10)));
   CHECK(Rational(5, -10) == Rational(-1, 2));
   CHECK_THROWS_WITH(Rational(1, 0), "denominator must not be equal to 0");
}
TEST_CASE("Operations")
{
  CHECK(-Rational(1, -5) == Rational(1, 5));
  CHECK(+Rational(1, -5) == Rational(-1, 5));

  CHECK(-Rational(1, -5)+Rational(1, -5) == Rational(0, 1));
  CHECK(Rational(1, -5)+Rational(1, -5) == Rational(-2, 5));
  CHECK(Rational(1, -5)-Rational(1, -5) == Rational(0, 1));
  CHECK(Rational(1, 5)*Rational(300, -5) == Rational(-12, 1));
  CHECK(Rational(1, 5)/Rational(300, -5) == Rational(-1, 300));
  CHECK_THROWS_WITH(Rational(1, 5) / Rational(0, 100), "You can not divide by 0");

  CHECK_THROWS_WITH(Rational(1, 5) /= Rational(0, 100), "You can not divide by 0");
  CHECK((-Rational(1, -5)+=Rational(1, -5)) == Rational(0, 1));
  CHECK((Rational(1, -5)+=Rational(1, -5)) == Rational(-2, 5));
  CHECK((Rational(1, -5)-=Rational(1, -5)) == Rational(0, 1));
  CHECK((Rational(1, 5)*=Rational(300, -5)) == Rational(-12, 1));
  CHECK((Rational(1, 5)/=Rational(300, -5)) == Rational(-1, 300));
  
  CHECK(++(Rational(1, -5)) == Rational(4, 5));
  CHECK((Rational(1, -5)++) == Rational(-1, 5));
  Rational c=Rational(1,5);
  Rational b=Rational(4,5);
  c=b++;
  CHECK(c==Rational(4,5));
  CHECK(b==Rational(9,5));
  c=++b;
  CHECK(c==Rational(14,5));
  CHECK(b==Rational(14,5));

  CHECK(--(Rational(1, -5)) == Rational(-6, 5));
  CHECK((Rational(1, -5)--) == Rational(-1, 5));
  c=Rational(1,5);
  b=Rational(4,5);
  c=b--;
  CHECK(c==Rational(4,5));
  CHECK(b==Rational(-1,5));
  c=--b;
  CHECK(c==Rational(-6,5));
  CHECK(b==Rational(-6,5));

  c=Rational(-4,5);
  b=Rational(3200,-160);
  c=b;
  CHECK(c==b);
}
TEST_CASE("Comparison") 
{
   CHECK(Rational(4, 5) > Rational(1, 3));
   CHECK(Rational(4, -5) < Rational(1, 3));
   CHECK(Rational(-3, -9) >= Rational(1, 3));
   CHECK (!(Rational(4,-5)<=Rational(-5,6)));
   CHECK(Rational(800, 800) <= Rational(1, 1));
   CHECK(Rational(4, 5) != Rational(1, 3));
   CHECK (!(Rational(4,-5)==Rational(-5,6)));
   CHECK(Rational(0, 5) == Rational());
}
TEST_CASE("Output") 
{
   Rational a(-400,-250);
   std::ostringstream output;
	output << a;
	CHECK(output.str() == "8/5");
}