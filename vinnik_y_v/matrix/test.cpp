#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "Matrix.h"
#include "doctest.h"

#include <iostream>

TEST_CASE("Testing init functions") {
	TableMatrix<int> m({
		{1, 0},
		{0, -1}
	});
	TableMatrix<int> m1(3, 2, 1);

	CHECK(m[0][0] == 1);
	CHECK(m.Columns() == 2);
	CHECK(m.Rows() == 2);
	CHECK(m.Get(1, 1) == -1);

	CHECK(m1.Rows() == 3);
	CHECK(m1.Columns() == 2);
	CHECK(m1.Get(0, 1) == 1);

	FlatMatrix<double> m2({
		{0.f, 0.f, 1.2f},
		{8.1f, 0.1f, 0.f},
		{0.5f, 0.32f, 11.f}
	});
	FlatMatrix<int> m3(1, 1);

	CHECK(m2.Rows() == 3);
	CHECK(m2.isSquare());
	CHECK(m2[1][1] == 0.1f);

	CHECK(m3.Columns() == m3.Rows());
	CHECK(m3[0][0] == 0);
}

TEST_CASE("Testing matrix core functionality") {
	FlatMatrix<double> m({
		{0.f, 0.f, 1.2f},
		{8.1f, 0.1f, 0.f},
		{0.5f, 0.32f, 11.f}
	});

	CHECK(m[2][1] == 0.32f);
	CHECK(m.Get(2, 2) == 11.f);
	CHECK_THROWS_WITH(m.Get(3, 3), "Matrix index is out of range");

	TableMatrix<int> m1(5, 5, 3);
	CHECK(m1[0][4] == 3);
	CHECK(m1.Rows() == 5);
	m1.Resize(1, 2);
	CHECK(m1.Rows() == 1);
	CHECK(m1.Columns() == 2);
	CHECK_THROWS_WITH(m1.Get(0, 4), "Matrix index is out of range");
}

TEST_CASE("Testing arithmetic operators") {
	FlatMatrix<int> m1({
		{0, 1},
		{5, 7},
	});

	FlatMatrix<int> m2({
		{0, -1},
		{2, -12}
	});

	FlatMatrix<int> m3 = m1 * m2;
	CHECK(m3 == FlatMatrix<int>({
		{ 2, -12 },
		{ 14, -89 }
	}));

	FlatMatrix<int> m4 = m2 * m1;
	CHECK(m4 == FlatMatrix<int>({
		{ -5, -7 },
		{ -60, -82 }
	}));

	TableMatrix<int> m5({
		{1},
		{8}
	});

	m5 *= 2;
	CHECK(m5 == TableMatrix<int>({
		{2},
		{16}
	}));
	m5 /= 2;
	CHECK(m5 == TableMatrix<int>({
		{1},
		{8}
	}));

	CHECK_THROWS_WITH(m5 /= 0, "Cannot divide matrix by 0");
	FlatMatrix<int> m6({
		{0, 1},
		{5, 7},
	});

	FlatMatrix<int> m7({
		{0, -1},
	});
	CHECK_THROWS_WITH(m6 * m7, "Cannot perform multiplication with given matrix");

	CHECK(m6 + m1 == FlatMatrix<int>({
		{0, 2},
		{10, 14}
	}));
}

TEST_CASE("Testing other functionality") {
	FlatMatrix<double> m({
		{0.f, 2.1f, 4.2f},
		{5.4f, 3.1f, 1.1f},
		{0.f, 1.1f, 0.1f}
	});

	m.Transponse();
	CHECK(m == FlatMatrix<double>({
		{0.f, 5.4f, 0.f},
		{2.1f, 3.1f, 1.1f},
		{4.2f, 1.1f, 0.1f}
	}));

	TableMatrix<double> m1({
		{0, 0},
		{0, 0},
	});

	TableMatrix<double> m2(2, 2);
	CHECK(m1 == m2);
}