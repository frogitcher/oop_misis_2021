#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "matrix.h"
#include "matrixf.h"
#include "matrixt.h"


TEST_CASE_TEMPLATE("Matrix constructors & operator[] & get", T, int, double, float, long long, char) {
	FlatMatrix<T> f1(13, 4, (T)16);
	TableMatrix<T> t1(13, 4, (T)(-5));
	FlatMatrix<T> f3(f1);
	TableMatrix<T> t3(t1);
	CHECK(f1.rows() == 13);
	CHECK(f1.colums() == 4);
	for (int i = 0; i < f1.rows(); i++) {
		for (int j = 0; j < f1.colums(); j++) {
			CHECK(f1[i][j] == (T)16);
			CHECK(f1.get(i, j) == (T)16);
			CHECK(t1[i][j] == (T)(-5));
			CHECK(t1.get(i, j) == (T)(-5));
			CHECK(f3[i][j] == (T)16);
			CHECK(t3[i][j] == (T)(-5));
		}
	}
	
	FlatMatrix<T> f2{ {(T)7, (T)9, (T)11}, {(T)13, (T)15, (T)17} };
	TableMatrix<T> t2{ {(T)6, (T)10, (T)14}, {(T)18, (T)22, (T)26} };
	CHECK(f2.rows() == 2);
	CHECK(f2.colums() == 3);
	T vf = (T)7;
	T vt = (T)6;
	for (int i = 0; i < f2.rows(); i++) {
		for (int j = 0; j < f2.colums(); j++) {
			CHECK(f2[i][j] == vf);
			CHECK(t2[i][j] == vt);
			vf += 2;
			vt += 4;
		}
	}

	CHECK_THROWS_WITH(FlatMatrix<T>(2, -5, (T)7), "the number of rows and colums must be positive");
	CHECK_THROWS_WITH(f2.get(3, -15), "index out of range");
	CHECK_THROWS_WITH(t2.get(-1, 8), "index out of range");
}

TEST_CASE_TEMPLATE("resize", T, int, double, float, long long, char) {
	FlatMatrix<T> f1(13, 4, (T)16);
	TableMatrix<T> t1(13, 4, (T)(-5));
	f1.resize(5, 3, (T)20);
	t1.resize(5, 3, (T)(-18));
	CHECK(f1.rows() == 5);
	CHECK(f1.colums() == 3);
	for (int i = 0; i < f1.rows(); i++) {
		for (int j = 0; j < f1.colums(); j++) {
			CHECK(f1[i][j] == (T)20);
			CHECK(t1[i][j] == (T)(-18));
		}
	}
	f1.resize(20, 5);
	t1.resize(20, 5);
	CHECK(f1.rows() == 20);
	CHECK(f1.colums() == 5);
	for (int i = 0; i < f1.rows(); i++) {
		for (int j = 0; j < f1.colums(); j++) {
			CHECK(f1[i][j] == (T)0);
			CHECK(t1[i][j] == (T)0);
		}
	}
}

TEST_CASE_TEMPLATE("operators with TableMatrix", T, int, double, float, long long) {
	TableMatrix<T> t1{ { (T)1, (T)5, (T)7 } ,{(T)2, (T)7, (T)8}, {(T)76, (T)356, (T)97} };
    TableMatrix<T> t2{ { (T)5, (T)8, (T)22} , {(T)34, (T)0, (T)(-13)}, {(T)8, (T)7, (T)(-7)}};
	TableMatrix<T> t3(t1);
	t1 *= t2;
	t3 = t3 * t2;
	CHECK(t1[0][0] == (T)231); CHECK(t1[0][1] == (T)57); CHECK(t1[0][2] == (T)(-92));
	CHECK(t1[1][0] == (T)312); CHECK(t1[1][1] == (T)72); CHECK(t1[1][2] == (T)(-103));
	CHECK(t1[2][0] == (T)13260); CHECK(t1[2][1] == (T)1287); CHECK(t1[2][2] == (T)(-3635));
	CHECK(t1 == t3);

	TableMatrix<T> t4{ { (T)1, (T)8, (T)9 } };
    TableMatrix<T> t5{ { (T)5}, { (T)(-5)},{ (T)(-13)}};
	t4 *= t5;
	CHECK(t4.rows() == 1);
	CHECK(t4.colums() == 1);
	CHECK(t4[0][0] == (T)(-152));

	TableMatrix<int> t6{ { 1 } ,{2}, {76} };
	TableMatrix<int> t7{ { 5, 8, 22}};
	t6 *= t7;
	CHECK(t6[0][0] == (T)5); CHECK(t6[0][1] == (T)8); CHECK(t6[0][2] == (T)22);
	CHECK(t6[1][0] == (T)10); CHECK(t6[1][1] == (T)16); CHECK(t6[1][2] == (T)44);
	CHECK(t6[2][0] == (T)380); CHECK(t6[2][1] == (T)608); CHECK(t6[2][2] == (T)1672);
	CHECK_FALSE(t6 == t7);
}

TEST_CASE_TEMPLATE("operators with FlatMatrix", T, int, double, float, long long) {
	FlatMatrix<T> t1{ { (T)1, (T)5, (T)7 } ,{(T)2, (T)7, (T)8}, {(T)76, (T)356, (T)97} };
	FlatMatrix<T> t2{ { (T)5, (T)8, (T)22} , {(T)34, (T)0, (T)(-13)}, {(T)8, (T)7, (T)(-7)} };
	FlatMatrix<T> t3(t1);
	t1 *= t2;
	t3 = t3 * t2;
	CHECK(t1[0][0] == (T)231); CHECK(t1[0][1] == (T)57); CHECK(t1[0][2] == (T)(-92));
	CHECK(t1[1][0] == (T)312); CHECK(t1[1][1] == (T)72); CHECK(t1[1][2] == (T)(-103));
	CHECK(t1[2][0] == (T)13260); CHECK(t1[2][1] == (T)1287); CHECK(t1[2][2] == (T)(-3635));
	CHECK(t1 == t3);

	FlatMatrix<T> t4{ { (T)1, (T)8, (T)9 } };
	FlatMatrix<T> t5{ { (T)5}, { (T)(-5)},{ (T)(-13)} };
	t4 *= t5;
	CHECK(t4.rows() == 1);
	CHECK(t4.colums() == 1);
	CHECK(t4[0][0] == (T)(-152));

	FlatMatrix<int> t6{ { 1 } ,{2}, {76} };
	FlatMatrix<int> t7{ { 5, 8, 22} };
	t6 *= t7;
	CHECK(t6[0][0] == (T)5); CHECK(t6[0][1] == (T)8); CHECK(t6[0][2] == (T)22);
	CHECK(t6[1][0] == (T)10); CHECK(t6[1][1] == (T)16); CHECK(t6[1][2] == (T)44);
	CHECK(t6[2][0] == (T)380); CHECK(t6[2][1] == (T)608); CHECK(t6[2][2] == (T)1672);
	CHECK_FALSE(t6 == t7);
}