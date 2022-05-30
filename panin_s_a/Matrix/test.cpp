#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Matrix.h"
#include <string>
// #include <iostream>
using namespace std;

TEST_CASE("Testing FlatMatrix constructors")
{
    FlatMatrix<int> m1(2, 5), m2(2, 5, -1), m3{{0, 1, 2, 3, 4}, {1, 2, 3, 4, 5}},  m4(m3);;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            CHECK(m1[i][j] == 0);
            CHECK(m2[i][j] == -1);
            CHECK(m3[i][j] == i + j);
            CHECK(m4[i][j] == i + j);
        }
    }
    m3.Resize(0, 0, 0);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 5; j++)
            CHECK(m4[i][j] == i + j);
    CHECK(m3.Rows() == 0);
    CHECK(m3.Cols() == 0);
    m3.Resize(5, 2, 113);
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 2; j++)
            CHECK(m3[i][j] == 113);
    CHECK(m3.Cols() == 2);
    CHECK(m3.Rows() == 5);
    CHECK(m3.Get(0, 0) == 113);
    CHECK_THROWS_WITH(FlatMatrix<int>(0, 5), "if one dimention is zero other also should be zero");
    CHECK_THROWS_WITH(FlatMatrix<int>({{1,2,3}, {1,2}, {12, 12, 12, 14}}), "number of elements in each row must be the same");
    CHECK_THROWS_WITH(m3.Get(-1, 0), "matrix index out of range");
}
