#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <string>
#include "doctest.h"
#include "Rational.h"
	

	TEST_CASE("Arithmetic operators") {
	
	    Rational a(10, 17), b(11, 13), c(5, 7), d(51, 3), e(-7, -17), f(13, -13), h(17, 5);
	
	    CHECK((a+b) == Rational(317, 221));
	    CHECK((a+c) == Rational(155, 119));
	    CHECK((a+d) == Rational(299, 17));
	    CHECK((a+e) == Rational(1));
	    CHECK((a+f) == Rational(-7, 17));
	    CHECK((a-h) == Rational(239, 85));
	    CHECK((a/e) == Rational(10, 7));

	    CHECK((a+=b) == Rational(317, 221));
	    CHECK((a*=h) == Rational(2));
	}
		
		TEST_CASE("Boolean operators") {
	
	    Rational a(1, 2), b(-111, -222), c(13, 15), d(17, -3);

	    CHECK((a == b) == true);
	    CHECK((a < d) == false);
	    CHECK((c > a) == true);
	    CHECK((d <= c) == true);
	    CHECK((a >= d) == true);
	    CHECK((b != c) == true);
	}
	
		TEST_CASE("Unary operators") {
	
	    Rational a(15);	

	    CHECK((++a) == Rational(16));
	    CHECK((a++) == Rational(16));
	    CHECK((--a) == Rational(16));
	    CHECK((a--) == Rational(16));
	}

	TEST_CASE("Denominator") {
	
	    Rational b(1, 2);
	
	    CHECK_THROWS_WITH(Rational(5, 0), "The denominator is just not 00");
	    CHECK_THROWS_WITH((b /= Rational(0, 5)), "The denominator is just not 0");
	}
	

	
