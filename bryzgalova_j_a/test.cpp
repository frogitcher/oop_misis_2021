#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include "matrix.h"




TEST_CASE("Matrix") {

	TableMatrix<int> m3 {{0, 1, 2}, {3, 4, 5}};

	TableMatrix<int> m4(m3);

	CHECK(m3==m4);

	m3.Resize(3, 3);

	CHECK(m3!=m4);

	m3=m3+10;

	CHECK(m3.Get(0, 0) == 10);

	CHECK(m3.Get(0, 1) == 1);

	CHECK(m3.Get(1, 1) == 14);

	m4.Resize(3, 3);

	m4=m4+m3;

	CHECK(m4.Get(0, 0) == 10);

	CHECK(m4.Get(0, 1) == 2);

	CHECK(m4.Get(1, 1) == 18);

	m4=m4-1;

	CHECK(m4.Get(0, 0) == 9);

	CHECK(m4.Get(0, 1) == 2);

	CHECK(m4.Get(1, 1) == 17);

	TableMatrix<int> m5 {{0, 1, 2}, {3, 4, 5}};

	TableMatrix<int> m6(m5);

	m6=m6*2;

	CHECK(m6.Get(0, 0) == 0);

	CHECK(m6.Get(0, 1) == 2);

	CHECK(m6.Get(1, 1) == 8);

	FlatMatrix<int> m1;

	CHECK(m1.Rows() == 0);

	CHECK(m1.Columns() == 0);

	FlatMatrix<int> m2(2, 3, 5);

	CHECK(m2.Rows() == 2);

	CHECK(m2.Columns() == 3);

	CHECK(m2.Get(1, 1) == 5);

	CHECK(m2.Get(1, 2) == 5);

	m2.Resize(3, 4);

	CHECK(m2.Rows() == 3);

	CHECK(m2.Columns() == 4);

	CHECK(m2.Get(1, 1) == 5);

	CHECK(m2.Get(2, 3) == 0);

	FlatMatrix<int> m3 {{0, 1, 2}, {3, 4, 5}};

	FlatMatrix<int> m4(m3);

	CHECK(m3==m4);

	m3.Resize(3, 3);

	CHECK(m3!=m4);

	m3=m3+10;

	CHECK(m3.Get(0, 0) == 10);

	CHECK(m3.Get(0, 1) == 1);

	CHECK(m3.Get(1, 1) == 14);

	m4.Resize(3, 3);

	m4=m4+m3;

	CHECK(m4.Get(0, 1) == 2);

	m4=m4-1;

	CHECK(m4.Get(0, 0) == 9);

	CHECK(m4.Get(0, 1) == 2);

	CHECK(m4.Get(1, 1) == 17);

	FlatMatrix<int> m5 {{0, 1, 2}, {3, 4, 5}};

	FlatMatrix<int> m6;

	m6=m5;

	m6=m6*(-1);

	CHECK(m6.Get(0, 0) == 0);

	CHECK(m6.Get(0, 1) == -1);

	CHECK(m6.Get(1, 1) == -4);

	m6.Resize(3, 3);

	CHECK(m5.Columns() == 3);

	CHECK(m6.Rows() == 3);

	TableMatrix<int> m1;

	CHECK(m1.Rows() == 0);

	CHECK(m1.Columns() == 0);

	TableMatrix<int> m2(2, 3, 5);

	CHECK(m2.Rows() == 2);

	CHECK(m2.Columns() == 3);

	CHECK(m2.Get(1, 1) == 5);

	CHECK(m2.Get(1, 2) == 5);

	m2.Resize(3, 4);

	CHECK(m2.Rows() == 3);

	CHECK(m2.Columns() == 4);

	CHECK(m2.Get(1, 1) == 5);

	CHECK(m2.Get(2, 3) == 0);

}