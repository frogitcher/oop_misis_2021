#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "BaseMatrix.h"


TEST_CASE("list") {
	ListMatrix<int> A({ { 1,1 }, { 2,2 } });
	ListMatrix<int> B({ { 1,1 }, { 2,2 } });
	ListMatrix<int> C(2, 2);
	ListMatrix<int> D(2, 2);
	C = A + B;
	D = A * 2;
	CHECK(C == D);
	ListMatrix<int> E({ { 0,0 }, { 0,0 } });
	CHECK(A - B == E);
	CHECK(A == B);
	ListMatrix<int> F({ {1}, {2}, {3} });
	ListMatrix<int> G({ {1, 2, 3} });
	CHECK(F * G == ListMatrix<int>({ {1, 2, 3}, {2, 4, 6}, {3, 6, 9} }));
	CHECK(A + 2 == 2 + A);
	CHECK_THROWS_WITH(G.Get(4, 4), "Out of range");
	CHECK_THROWS_WITH(G[4][4], "Out of range");
	CHECK_THROWS_WITH(G + B, "different size!");
	CHECK_THROWS_WITH(G + 2, "Wrong size!");
	CHECK_THROWS_WITH(A * G, "Wrong size!");
	ListMatrix<int> CC({
		{1, 3, 5},
		{2, 4, 6},
		});
	ListMatrix<int> CCC({
		{1, 3, 5, 0},
		{2, 4, 6, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		});
	CC.Resize(4, 4);
	CHECK(CC == CCC);
	
}
TEST_CASE("Flat") {
	FlatMatrix<int> A({ { 1,1 }, { 2,2 } });
	CHECK(A.Get(0, 0) == 1);
	CHECK(A.Row_() == 2);
	CHECK(A.Col_() == 2);
	FlatMatrix<int> B({ { 1,1 }, { 2,2 } });
	FlatMatrix<int> C(2,2);
	FlatMatrix<int> D(2,2);
	C = A + B;
	D = A * 2;
	CHECK(C == D);
	FlatMatrix<int> E({ { 0,0 }, { 0,0 } });
	CHECK(A - B == E);
	CHECK(A == B);
	FlatMatrix<int> F({{1}, {2}, {3}});
	FlatMatrix<int> G({{1, 2, 3}});
	CHECK(F * G == FlatMatrix<int>({ {1, 2, 3}, {2, 4, 6}, {3, 6, 9} }));
	CHECK(A + 2 == 2 + A);
	CHECK_THROWS_WITH(G.Get(4,4), "Out of range");
	CHECK_THROWS_WITH(G[4][4], "Out of range");
	CHECK_THROWS_WITH(G + B, "different size!");
	CHECK_THROWS_WITH(G + 2, "Wrong size!");
	CHECK_THROWS_WITH(A * G, "Wrong size!");
}