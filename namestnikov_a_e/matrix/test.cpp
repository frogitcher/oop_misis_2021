#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Matrix.h"
#include <string>

TEST_CASE("Testing FlatMatrix functions")
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
    CHECK_THROWS_WITH(FlatMatrix<int>(0, 5), "Matrix must be square");
    CHECK_THROWS_WITH(FlatMatrix<int>({{1,2,3}, {1,2}, {12, 12, 12, 14}}), "Matrix must be square");
    CHECK_THROWS_WITH(m3.Get(-1, 0), "Index out of range");
    FlatMatrix<int> m5{{4, 5}, {6, 13}}, m6{{1, 2}, {1, 2}}, m7{{2, 1}, {2, 1}}, m8{{3, 3}, {3, 3}};
    FlatMatrix<int> m9{{-1, 1}, {-1, 1}}, m10{{10, 20}, {10, 20}};
    CHECK(m5[0][0] == 4);
    CHECK(m5[0][1] == 5);
    CHECK(m5[1][0] == 6);
    CHECK(m5[1][1] == 13);
    CHECK(m6 + m7 == m8);
    CHECK(m6 - m7 == m9);
    CHECK(m6 * (int)10 == m10);
    FlatMatrix<int> m11 = m10;
    CHECK(m10[0][0] == 10);
    CHECK(m10[0][1] == 20);
    CHECK(m10[1][0] == 10);
    CHECK(m10[1][1] == 20);
    CHECK(m1 != m2);
    FlatMatrix<int> left{{1, 2}, {3, 4}}, right{{5, 6}, {7, 8}}, res{{19, 22}, {43, 50}};
    FlatMatrix<int> rr = left * right;
    CHECK( left * right == res);
    CHECK(rr == res);
    CHECK((left * right == res));
}

TEST_CASE("Testing TableMatrix functions")
{
    TableMatrix<int> m1(2, 5), m2(2, 5, -1), m3{{0, 1, 2, 3, 4}, {1, 2, 3, 4, 5}},  m4(m3);
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
    CHECK_THROWS_WITH(TableMatrix<int>(0, 5), "Matrix must be square");
    CHECK_THROWS_WITH(TableMatrix<int>({{1,2,3}, {1,2}, {12, 12, 12, 14}}), "Matrix must be square");
    CHECK_THROWS_WITH(m3.Get(-1, 0), "Index out of range");
    TableMatrix<int> m5{{4, 5}, {6, 13}}, m6{{1, 2}, {1, 2}}, m7{{2, 1}, {2, 1}}, m8{{3, 3}, {3, 3}};
    TableMatrix<int> m9{{-1, 1}, {-1, 1}}, m10{{10, 20}, {10, 20}};
    CHECK(m5[0][0] == 4);
    CHECK(m5[0][1] == 5);
    CHECK(m5[1][0] == 6);
    CHECK(m5[1][1] == 13);
    CHECK(m6 + m7 == m8);
    CHECK(m6 - m7 == m9);
    CHECK(m6 * (int)10 == m10);
    TableMatrix<int> m11 = m10;
    CHECK(m10[0][0] == 10);
    CHECK(m10[0][1] == 20);
    CHECK(m10[1][0] == 10);
    CHECK(m10[1][1] == 20);
    CHECK(m1 != m2);
    TableMatrix<int> left{{1, 2}, {3, 4}}, right{{5, 6}, {7, 8}}, res{{19, 22}, {43, 50}};
    TableMatrix<int> rr = left * right;
    CHECK( left * right == res);
    CHECK(rr == res);
    CHECK((left * right == res));
}