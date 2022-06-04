#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dinmas.h"


TEST_CASE("array") {
	dinmas A{ 1,2,3,4,5 };
	dinmas B{ 10,9,8,7,6,5,4,3 };
	dinmas C{ 0,1 };
	dinmas D{ 0,1 };
	dinmas E{ 1,2,3,4,5,6 };
	CHECK(C.Size() == 2);
	CHECK(B.Size() == 8);
	CHECK(C == D);
	CHECK(C != A);
	CHECK(A.Empty() == false);
	A.push_back(6);
	CHECK(A == E);
	A.assign(2, 111);
	CHECK(A == dinmas({ 111,111 }));
	CHECK(A.Size() == 2);
	dinmas G;
	CHECK(G.Size() == 0);
	CHECK(G.Capacity() == 0);
	G.push_back(100);
	CHECK(G.Size() == 1);
	CHECK(G == dinmas({ 100 }));
	B.Erase(4);
	CHECK(B == dinmas({ 10,9,8,7,5,4,3 }));
	CHECK(B.Size() == 7);
	dinmas H{ 1,2,3,4 };
	H.insert(2, 2022);
	CHECK(H == dinmas({ 1,2,2022,3,4 }));
	CHECK(H.at(2) == 2022);
	dinmas I{1, 1, 1, 1, 1, 1, 1};
	H.swap(I);
	CHECK(H.Size() == 7);
	CHECK(H.at(2) == 1);
	dinmas J;
	CHECK(J.Size() == 0);
	CHECK_THROWS_WITH(J.pop_back(), "Array size 0");
	CHECK_THROWS_WITH(J.insert(999, 7), "Out of range");
	CHECK_THROWS_WITH(J.Erase(999), "Array size 0");
	CHECK_THROWS_WITH(J.at(1), "Going beyond the borders!");
}