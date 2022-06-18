#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "flat_matrix.h"
#include "table_matrix.h"

TEST_CASE_TEMPLATE("FLAT MATRIX", T, int, float, double, long long) {
    FlatMatrix<T> a(3, 4, 5), b({{1, 2},
                                 {3, 4},
                                 {5, 6},
                                 {7, 8}}), c(3, 4, -3), d(3, 3);

    CHECK(a.Rows() == 3);
    CHECK(a.Cols() == 4);
    CHECK(b.Rows() == 4);
    CHECK(b.Cols() == 2);

    CHECK(a + c == FlatMatrix<T>(3, 4, 2));
    CHECK(d + 9 == FlatMatrix<T>({{9, 0, 0},
                                  {0, 9, 0},
                                  {0, 0, 9}}));

    CHECK(c - a == FlatMatrix<T>(3, 4, -8));
    CHECK(d - 9 == FlatMatrix<T>({{-9, 0,  0},
                                  {0,  -9, 0},
                                  {0,  0,  -9}}));

    CHECK(a * b == FlatMatrix<T>({{80, 100},
                                  {80, 100},
                                  {80, 100}}));
    CHECK(b * 5 == FlatMatrix<T>({{5,  10},
                                  {15, 20},
                                  {25, 30},
                                  {35, 40}}));

    CHECK_FALSE(a == b);
    CHECK(a * 3 == c * -5);
    CHECK(a != b);

    c = d + 3;
    CHECK(c == FlatMatrix<T>({{3, 0, 0},
                              {0, 3, 0},
                              {0, 0, 3}}));
    CHECK(c[0][0] == 3);
    CHECK(c[0][1] == 0);
    CHECK(c.Get(0, 0) == 3);
    CHECK(c.Get(0, 1) == 0);

    c.Resize(5, 5);
    CHECK(c == FlatMatrix<T>({{3, 0, 0, 0, 0},
                              {0, 3, 0, 0, 0},
                              {0, 0, 3, 0, 0},
                              {0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0}}));
    c.Resize(1, 1);
    CHECK(c == FlatMatrix<T>({{3}}));

    CHECK_THROWS_WITH(a + b, "Error");
    CHECK_THROWS_WITH(a - d, "Error");
    CHECK_THROWS_WITH(a + 3, "Error");
    CHECK_THROWS_WITH(a - 2, "Error");
    CHECK_THROWS_WITH(a * c, "Error");
}


TEST_CASE_TEMPLATE("TABLE MATRIX", T, int, float, double, long long) {
    TableMatrix<T> a(3, 4, 5), b({{1, 2},
                                  {3, 4},
                                  {5, 6},
                                  {7, 8}}), c(3, 4, -3), d(3, 3);

    CHECK(a.Rows() == 3);
    CHECK(a.Cols() == 4);
    CHECK(b.Rows() == 4);
    CHECK(b.Cols() == 2);

    CHECK(a + c == TableMatrix<T>(3, 4, 2));
    CHECK(d + 9 == TableMatrix<T>({{9, 0, 0},
                                   {0, 9, 0},
                                   {0, 0, 9}}));

    CHECK(c - a == TableMatrix<T>(3, 4, -8));
    CHECK(d - 9 == TableMatrix<T>({{-9, 0,  0},
                                   {0,  -9, 0},
                                   {0,  0,  -9}}));

    CHECK(a * b == TableMatrix<T>({{80, 100},
                                   {80, 100},
                                   {80, 100}}));
    CHECK(b * 5 == TableMatrix<T>({{5,  10},
                                   {15, 20},
                                   {25, 30},
                                   {35, 40}}));

    CHECK_FALSE(a == b);
    CHECK(a * 3 == c * -5);
    CHECK(a != b);

    c = d + 3;
    CHECK(c == TableMatrix<T>({{3, 0, 0},
                               {0, 3, 0},
                               {0, 0, 3}}));
    CHECK(c[0][0] == 3);
    CHECK(c[0][1] == 0);
    CHECK(c.Get(0, 0) == 3);
    CHECK(c.Get(0, 1) == 0);

    c.Resize(5, 5);
    CHECK(c == TableMatrix<T>({{3, 0, 0, 0, 0},
                               {0, 3, 0, 0, 0},
                               {0, 0, 3, 0, 0},
                               {0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0}}));
    c.Resize(1, 1);
    CHECK(c == TableMatrix<T>({{3}}));

    CHECK_THROWS_WITH(a + b, "Error");
    CHECK_THROWS_WITH(a - d, "Error");
    CHECK_THROWS_WITH(a + 3, "Error");
    CHECK_THROWS_WITH(a - 2, "Error");
    CHECK_THROWS_WITH(a * c, "Error");
}
