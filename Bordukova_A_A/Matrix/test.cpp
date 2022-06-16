#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "FlatMatrix.h"
#include "TableMatrix.h"

TEST_CASE_TEMPLATE("Testing Flat Matrix", T, int, float, long long, double) {
	//Constutuctors
	FlatMatrix<T> fm(3, 7, 90);
	CHECK(fm.Rows() == 3);
	CHECK(fm.Columns() == 7);
	/*for (size_t i = 0; i < fm.Rows() * fm.Columns(); ++i) {
		CHECK(Get_Data(fm)[i] == 90);
	}*/
	FlatMatrix<T> fm1(3, 3, 1);
	CHECK(fm1.Is_Square());
	FlatMatrix<T> fm2(56, 21, 0);
	CHECK_FALSE(fm2.Empty());

	FlatMatrix<T> fl({ {11, 62, 73}, {48, 65, 96}, {17, 38, 49} });
	CHECK(fl.Columns() == 3);
	CHECK(fl.Rows() == 3);
	CHECK(fl.Is_Square());
	//CHECK(Get_Data(fl)[5] == 65);

	FlatMatrix<T> fe;
	CHECK(fe.Rows() == 0);
	CHECK(fe.Columns() == 0);
	CHECK(fe.Empty());
	CHECK_FALSE(fm1.Empty());

	//Logical functions
	FlatMatrix<T> fm_copy(fm);
	CHECK(fm_copy == fm);
	CHECK(fe != fm);
	CHECK_FALSE(fm == fe);
	FlatMatrix<T> fm1_copy(fm1);
	CHECK(fm1_copy != fm_copy);

	//Pointers
	CHECK(fm1.Get(0, 0) == 1);
	CHECK(fm1[0][0] == 1);
	fm[0][0] = 987;
	CHECK(fm.Get(0, 0) == 987);
	CHECK(fm[0][0] == 987);
	CHECK(fm2[0][20] == 0);
	fm2[0][20] = 12;
	CHECK(fm2.Get(0, 20) == 12);

	FlatMatrix<T> fm3(56, 21, 0);
	fm3.Resize(11, 3, 87);
	CHECK(fm3.Rows() == 11);
	CHECK(fm3.Columns() == 3);
	CHECK(fm3.Get(3, 0) == 0);
	CHECK(fm3[0][3] == 0);
	CHECK_FALSE(fm3.Empty());
	CHECK_FALSE(fm3.Is_Square());


	//Arithmetical operators
	CHECK(FlatMatrix<T>(2, 3, 45) + FlatMatrix<T>(2, 3, 61) == FlatMatrix<T>(2, 3, 106));
	//CHECK_THROWS_WITH(FlatMatrix<T>(3, 3, 45) + FlatMatrix<T>(2, 3, 61), "Matrix must be the same size!")
	CHECK(FlatMatrix<T>(19, 31, 11) - FlatMatrix<T>(19, 31, 11) == FlatMatrix<T>(19, 31, 0));
	//CHECK_THROWS_WITH(FlatMatrix<T>(12, 6, 98) + FlatMatrix<T>(12, 5, 98), "Matrix must be the same size!")
	CHECK(FlatMatrix<T>(2, 3, 2) * FlatMatrix<T>(3, 2, 3) == FlatMatrix<T>(2, 2, 18));
	//CHECK_THROWS_WITH(FlatMatrix<T>(12, 6, 98) * FlatMatrix<T>(12, 5, 98), "Matrix must be the same size!")

	FlatMatrix<T> a({ {19, 19}, {19, 19}, {19, 19}, {19, 19} });
	a += FlatMatrix<T>({ {1, 1}, {1, 1}, {1, 1}, {1, 1} });
	CHECK(a == FlatMatrix<T>({ {20, 20}, {20, 20}, {20, 20}, {20, 20} }));
	a -= FlatMatrix<T>({ {1, 2}, {3, 4}, {5, 6}, {7, 8} });
	CHECK(a == FlatMatrix<T>({ {19, 18}, {17, 16}, {15, 14}, {13, 12} }));
	a *= FlatMatrix<T>({ {7, 5}, {6, 4} });
	CHECK(a == FlatMatrix<T>({ {241, 167}, {215, 149}, {189, 131}, {163, 113} }));
	//CHECK_THROWS_WITH(a *= FlatMatrix<T>({ {6, 4} }); , "Number of the rows in the first matrix must be the same as the number of columns in the second one!")
}

TEST_CASE_TEMPLATE("Testing Table Matrix", T, int, float, long long, double) {

	//Constutuctors
	TableMatrix<T> tm(2, 5, 13);
	CHECK(tm.Rows() == 2);
	CHECK(tm.Columns() == 5);
	/*for (size_t i = 0; i < tm.Rows() - 1; ++i) {
		for (size_t j = 0; j < tm.Columns(); ++j) {
			CHECK(Get_Data(tm)[i][j] == 13);
		}
	}*/

	TableMatrix<T> tl({ {11, 62, 73}, {48, 65, 96}, {17, 38, 49} });
	CHECK(tl.Columns() == 3);
	CHECK(tl.Rows() == 3);
	CHECK(tl.Is_Square());
//	CHECK(Get_Data(tl)[5] == 65);

	TableMatrix<T> te;
	CHECK(te.Rows() == 0);
	CHECK(te.Columns() == 0);
	CHECK(te.Empty());
	CHECK_FALSE(tm.Empty());

	//Logical functions
	TableMatrix<T> tm_copy (tm);
	CHECK(tm_copy == tm);
	CHECK(te != tm);
	CHECK_FALSE(tm == te);

	//Pointers
	CHECK(tm.Get(0, 0) == 13);
	CHECK(tm[0][0] == 13);
	tm[0][0] = 987;
	CHECK(tm.Get(0, 0) == 987);
	CHECK(tm[0][0] == 987);

	tm.Resize(11, 3, 87);
	CHECK(tm.Rows() == 11);
	CHECK(tm.Columns() == 3);
	CHECK(tm.Get(3, 0) == 87);
	CHECK_FALSE(tm.Empty());
	CHECK_FALSE(tm.Is_Square());

	//Arithmetical operators
	CHECK(TableMatrix<T>(2, 3, 76) + TableMatrix<T>(2, 3, 63) == TableMatrix<T>(2, 3, 139));
	//CHECK_THROWS_WITH(TableMatrix<T>(3, 3, 45) + TableMatrix<T>(2, 3, 61), "Matrix must be the same size!")
	CHECK(TableMatrix<T>(9, 31, 11) - TableMatrix<T>(9, 31, 11) == TableMatrix<T>(9, 31, 0));
	//CHECK_THROWS_WITH(TableMatrix<T>(12, 6, 98) + TableMatrix<T>(12, 5, 98), "Matrix must be the same size!")
	CHECK(TableMatrix<T>(2, 3, 2) * TableMatrix<T>(3, 2, 3) == TableMatrix<T>(2, 2, 18));
	//CHECK_THROWS_WITH(TableMatrix<T>(12, 6, 98) * TableMatrix<T>(12, 5, 98), "Matrix must be the same size!")

	TableMatrix<T> a({ {19, 19}, {19, 19}, {19, 19}, {19, 19} });
	a += TableMatrix<T>({ {1, 1}, {1, 1}, {1, 1}, {1, 1} });
	CHECK(a == TableMatrix<T>({ {20, 20}, {20, 20}, {20, 20}, {20, 20} }));
	a -= TableMatrix<T>({ {1, 2}, {3, 4}, {5, 6}, {7, 8} });
	CHECK(a == TableMatrix<T>({ {19, 18}, {17, 16}, {15, 14}, {13, 12} }));
	a *= TableMatrix<T>({ {7, 5}, {6, 4} });
	CHECK(a == TableMatrix<T>({ {241, 167}, {215, 149}, {189, 131}, {163, 113} }));
	//CHECK_THROWS_WITH(a *= TableMatrix<T>({ {6, 4} });, "Number of the rows in the first matrix must be the same as the number of columns in the second one!")

}