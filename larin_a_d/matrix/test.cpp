#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "FlatMatrix.h"
#include "TableMatrix.h"
#include "doctest.h"

TEST_CASE("Testing table matrix") {
	TableMatrix<int> m1(3, 2, 1);
	CHECK(m1[0][0] == 1);
	CHECK_FALSE(m1[1][0] == 2);
	CHECK(m1.Get_rows() == 3);
	CHECK(m1.Get_cols() == 2);
	m1[0][0] = 5;
	CHECK(m1.Get(0, 0) == 5);
	TableMatrix<int> m2(3, 2, 1);
	m2[0][0] = 5;
	CHECK(m1 == m2);
	m1 += m2;
	CHECK_FALSE(m1 == m2);
	CHECK(m1[0][0] == 10);
	m1 -= m2;
	CHECK(m1 == m2);
	m1.Resize(2, 2, 2);
	CHECK(m1.Get_cols() == 2);
	CHECK(m1.Get_rows() == 2);
	CHECK(m1[1][1] == 2);
	CHECK_THROWS_WITH(m1.Get(1, 2), "Out of range!");
	m2.Resize(2, 2, 3);
	TableMatrix<int> m3({
		{1, 3},
		{3, 4}
		});
	m1 *= m3;
	CHECK(m1 == TableMatrix<int>({
		{ 8, 14 },
		{ 8, 14 }
		}));
	TableMatrix<float> m4({
		{1, 2},
		{3, 4},
		{-5, -6}
		});
	TableMatrix<float> m5({
		{1, -1.7},
		{2.8, -2}
		});
	CHECK_THROWS_WITH(TableMatrix<float> res = m4 - m5, "Out of range!");
}

TEST_CASE("Testing flat matrix") {
	FlatMatrix<int> m1(3, 2, 1);
	CHECK(m1[0][0] == 1);
	CHECK_FALSE(m1[1][0] == 2);
	CHECK(m1.Get_rows() == 3);
	CHECK(m1.Get_cols() == 2);
	m1[0][0] = 5;
	CHECK(m1.Get(0, 0) == 5);
	FlatMatrix<int> m2(3, 2, 1);
	m2[0][0] = 5;
	CHECK(m1 == m2);
	m1 += m2;
	CHECK_FALSE(m1 == m2);
	CHECK(m1[0][0] == 10);
	m1 -= m2;
	CHECK(m1 == m2);
	m1.Resize(2, 2, 2);
	CHECK(m1.Get_cols() == 2);
	CHECK(m1.Get_rows() == 2);
	CHECK(m1[1][1] == 2);
	CHECK_THROWS_WITH(m1.Get(1, 2), "Out of range!");
	m2.Resize(2, 2, 3);
	FlatMatrix<int> m3({
		{1, 3},
		{3, 4}
		});
	m1 *= m3;
	CHECK(m1 == FlatMatrix<int>({
		{ 8, 14 },
		{ 8, 14 }
		}));
}