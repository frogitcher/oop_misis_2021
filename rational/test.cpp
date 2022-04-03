#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

TEST_CASE("Testing output"){
    std::stringstream teststream;
    teststream << Rational(1, 2);
    CHECK(teststream.str() == "1/2");
}

TEST_CASE("Testing arithmetic operations") {
    CHECK(Rational(100, 1000) == Rational(1, 10));
    CHECK(Rational(1, 2) + Rational(1, 2) == Rational(1, 1));
    CHECK(Rational(3, 3) - Rational(1, 2) == Rational(2, 4));
    CHECK(Rational(1, 3) - Rational(5, 3) == Rational(-4, 3));
    CHECK(Rational(2, 5) * Rational(1, 2) == Rational(2, 10));
    CHECK(Rational(5, 1) / Rational(1, 2) == Rational(10, 1));
    CHECK(Rational(4, 3) / Rational(-3, 4) == Rational(-16, 9));
    CHECK((Rational(5, 1) += Rational(3, 1)) == Rational(8, 1));
    CHECK((Rational(5, 1) *= Rational(0, 5)) == Rational(0));
    CHECK((Rational(7, 2) -= Rational(0, 5723)) == Rational(7, 2));
    CHECK((Rational(8, 2) /= Rational(1, 2)) == Rational(8, 1));

    CHECK(Rational(121, 242) + Rational(121, 242) == Rational(1, 1));
    CHECK(Rational(237716, 275) - Rational(51673, 671) == Rational(13208851, 16775));
    CHECK(Rational(8553467, 51653) - Rational(93545, 250) == Rational(-538702627, 2582650));
    CHECK(Rational(34625, 24513) * Rational(6791, 7973) == Rational(235138375, 1954422149));
    CHECK(Rational(3462, 8551) / Rational(9515, 7217) == Rational(24985254, 81362765));
    CHECK(Rational(3462, 8551) / Rational(9515, -7217) == Rational(-24985254, 81362765));
    CHECK((Rational(3555, 7976) += Rational(6761, 9515)) == Rational(87751561, 75891640));
    CHECK((Rational(34625, 8551) *= Rational(6791, 7973)) == Rational(235138375, 1954422149));
    CHECK((Rational(8553467, 51653) -= Rational(93545, 250)) == Rational(-538702627, 2582650));
    CHECK((Rational(3462, 8551) /= Rational(9515, 7217)) == Rational(24985254, 81362765));
}

TEST_CASE("Testing boolean functions (True cases)") {

    CHECK(Rational(1, -1) == Rational(-1, 1));
    CHECK(Rational(-1, 1) != Rational(1, 1));
    CHECK(Rational(20, 1) > Rational(1, 20));
    CHECK(Rational(-6, 9) < (Rational(5, -9)));
    CHECK(Rational(4, 7) >= (Rational(7, 31)));
    CHECK(Rational(4, 7) >= (Rational(4, 7)));
    CHECK(Rational(3, 14) <= (Rational(7, 15)));
    CHECK(Rational(3, 14) <= (Rational(3, 14)));

}

TEST_CASE("Testing boolean functions (False cases)") {

    CHECK(!(Rational(10, 1) == Rational(9, 1)));
    CHECK(!(Rational(10, 5) == Rational(12, 4)));
    CHECK(!(Rational(-1, 1) != Rational(-1, 1)));
    CHECK(!(Rational(1, 20) > Rational(20, 1)));
    CHECK(!(Rational(-6, 9) < (Rational(8, -9)));
    CHECK(!(Rational(-4, 7) >= (Rational(7, 31)));
    CHECK(!(Rational(3, 7) >= (Rational(4, 7)));
    CHECK(!(Rational(15, 14) <= (Rational(7, 15)));
    CHECK(!(Rational(3, 14) <= (Rational(4, 14)));

}

TEST_CASE("Testing exceptions") {
    CHECK_THROWS_WITH(Rational(1, 0), "denominator must not be 0");
    CHECK_THROWS_WITH((Rational(4, 9) /= Rational(0, 23)), "division by 0");
}
