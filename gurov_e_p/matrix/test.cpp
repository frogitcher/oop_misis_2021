#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "flat_matrix.h"
#include "table_matrix.h"

TEST_CASE_TEMPLATE("Testing Flat Matrix", T, int, float, long long, double) {
	// constructor, row and col number, all elements assigned correctly
	FlatMatrix<T> fm(2, 5, 3);
	CHECK(fm.Rows() == 2);
	CHECK(fm.Cols() == 5);
	for (size_t i = 0; i < fm.Rows() * fm.Cols(); ++i) {
		CHECK(Get_Data(fm)[i] == 3);
	}

	// init list constructor
	FlatMatrix<T> from_list({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
	CHECK(from_list.Cols() == 3);
	CHECK(from_list.Rows() == 3);
	for (size_t i = 0; i < 9; ++i) {
		CHECK(Get_Data(from_list)[i] == i + 1);
	}

	// constructor, row and col number with an empty matrix
	// Empty() on both empty and filled matrices
	FlatMatrix<T> fm_empty;
	CHECK(fm_empty.Rows() == 0);
	CHECK(fm_empty.Cols() == 0);
	CHECK(fm_empty.Empty());
	CHECK_FALSE(fm.Empty());

	// copy constructor, == and != operators
	FlatMatrix<T> fm_copy(fm);
	CHECK(fm_copy == fm);
	CHECK(fm_empty != fm);
	CHECK_FALSE(fm == fm_empty);

	// element assignment
	CHECK(fm.Get(0, 0) == 3);
	CHECK(fm[0][0] == 3);
	fm[0][0] = 500;
	CHECK(fm.Get(0, 0) == 500);
	CHECK(fm[0][0] == 500);

	// Resize()
	fm.Resize(11, 1, 89);
	CHECK(fm.Rows() == 11);
	CHECK(fm.Cols() == 1);
	CHECK(fm.Get(10, 0) == 89);
	CHECK(fm[10][0] == 89);

	// arithmetics
	CHECK(FlatMatrix<T>(2, 3, 4) + FlatMatrix<T>(2, 3, 6) == FlatMatrix<T>(2, 3, 10));
	CHECK(FlatMatrix<T>(9, 1, 1) - FlatMatrix<T>(9, 1, 1) == FlatMatrix<T>(9, 1, 0));
	CHECK(FlatMatrix<T>(4, 3, 5) * FlatMatrix<T>(3, 2, 2) == FlatMatrix<T>(4, 2, 30));
	CHECK(FlatMatrix<T>(1, 5, 1) * FlatMatrix<T>(5, 1, 3) == FlatMatrix<T>(1, 1, 15));
	CHECK(FlatMatrix<T>(5, 1, 1) * FlatMatrix<T>(1, 5, 3) == FlatMatrix<T>(5, 5, 3));

	FlatMatrix<T> a({{9, 9}, {9, 9}, {9, 9}, {9, 9}});
	a += FlatMatrix<T>({{1, 1}, {1, 1}, {1, 1}, {1, 1}});
	CHECK(a == FlatMatrix<T>({{10, 10}, {10, 10}, {10, 10}, {10, 10}}));
	a -= FlatMatrix<T>({{1, 2}, {3, 4}, {5, 6}, {7, 8}});
	CHECK(a == FlatMatrix<T>({{9, 8}, {7, 6}, {5, 4}, {3, 2}}));
	a *= FlatMatrix<T>({{-1, 0}, {13, 4}});
	CHECK(a == FlatMatrix<T>({{95, 32}, {71, 24}, {47, 16}, {23, 8}}));
}

 TEST_CASE_TEMPLATE("Testing Table Matrix", T, int, float, long long, double) {
	// constructor, row and col number, all elements assigned correctly
	TableMatrix<T> tm(2, 5, 3);
	CHECK(tm.Rows() == 2);
	CHECK(tm.Cols() == 5);
	for (size_t i = 0; i < tm.Rows() - 1; ++i) {
		for (size_t j = 0; j < tm.Cols(); ++j) {
			CHECK(Get_Data(tm)[i][j] == 3);
		}
	}

	// init list constructor
	TableMatrix<T> from_list({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
	CHECK(from_list.Cols() == 3);
	CHECK(from_list.Rows() == 3);
	CHECK(from_list == TableMatrix<T>({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));
	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 3; ++j) {
			CHECK(Get_Data(from_list)[i][j] == (i * 3) + j + 1);
		}
	}

	// constructor, row and col number with an empty matrix
	// Empty() on both empty and filled matrices
	TableMatrix<T> tm_empty;
	CHECK(tm_empty.Rows() == 0);
	CHECK(tm_empty.Cols() == 0);
	CHECK(tm_empty.Empty());
	CHECK_FALSE(tm.Empty());

	// copy constructor, == and != operators
	 TableMatrix<T> tm_copy(tm);
	CHECK(tm_copy == tm);
	CHECK(tm_empty != tm);
	CHECK_FALSE(tm == tm_empty);

	// element assignment
	CHECK(tm.Get(0, 0) == 3);
	CHECK(tm[0][0] == 3);
	tm[0][0] = 500;
	CHECK(tm.Get(0, 0) == 500);
	CHECK(tm[0][0] == 500);

	// Resize()
	tm.Resize(11, 1, 89);
	CHECK(tm.Rows() == 11);
	CHECK(tm.Cols() == 1);
	CHECK(tm.Get(10, 0) == 89);
	CHECK(tm[10][0] == 89);

	// arithmetics
	CHECK(TableMatrix<T>(2, 3, 4) + TableMatrix<T>(2, 3, 6) == TableMatrix<T>(2, 3, 10));
	CHECK(TableMatrix<T>(9, 1, 1) - TableMatrix<T>(9, 1, 1) == TableMatrix<T>(9, 1, 0));
	CHECK(TableMatrix<T>(4, 3, 5) * TableMatrix<T>(3, 2, 2) == TableMatrix<T>(4, 2, 30));
	CHECK(TableMatrix<T>(1, 5, 1) * TableMatrix<T>(5, 1, 3) == TableMatrix<T>(1, 1, 15));
	CHECK(TableMatrix<T>(5, 1, 1) * TableMatrix<T>(1, 5, 3) == TableMatrix<T>(5, 5, 3));

	TableMatrix<T> a({{9, 9}, {9, 9}, {9, 9}, {9, 9}});
	a += TableMatrix<T>({{1, 1}, {1, 1}, {1, 1}, {1, 1}});
	CHECK(a == TableMatrix<T>({{10, 10}, {10, 10}, {10, 10}, {10, 10}}));
	a -= TableMatrix<T>({{1, 2}, {3, 4}, {5, 6}, {7, 8}});
	CHECK(a == TableMatrix<T>({{9, 8}, {7, 6}, {5, 4}, {3, 2}}));
	a *= TableMatrix<T>({{-1, 0}, {13, 4}});
	CHECK(a == TableMatrix<T>({{95, 32}, {71, 24}, {47, 16}, {23, 8}}));
 }
