#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "matrix.h"

TEST_CASE("TEST Flat_Matrix's Get, Row, Col and [ ]"){
    FlatMatrix<int> a(5, 6);
    CHECK(a.Get(1, 2) == 0);
    a[0][4] = 1;
    a[0][5] = 1;
    a[1][0] = 1;
    a[0][0] = 10;
    CHECK(a.Get(0, 0) == 10);
    CHECK(a.Get(0, 5) == 1);
    CHECK(*a[1] == 1);
    CHECK(*a[0] == 10);
    CHECK(a.Row() == 5);
    CHECK(a.Col() == 6);


    FlatMatrix<int> b(2, 2), c(2, 2);
    FlatMatrix<int> d({
		{2, 1},
		{5, 7},
	});
	CHECK_THROWS_WITH(FlatMatrix<int> e({{2},{5, 7}}), "impossible to create a matrix");
	CHECK(d.Get(0, 0) == 2);
	CHECK(d.Get(0, 1) == 1);
	CHECK(d.Get(1, 0) == 5);
	CHECK(d.Get(1, 1) == 7);

    b[0][0] = 1;
    b[0][1] = 1;
    b[1][0] = 1;
    b[1][1] = 1;
    c[0][0] = 2;
    c[0][1] = 2;
    c[1][0] = 2;
    c[1][1] = 2;
    CHECK((b+c).Row() == 2);
    CHECK((b+c).Col() == 2);
    CHECK(*((b+c)[0]) == 3);
    CHECK(*((b+c)[1]) == 3);
}

TEST_CASE("TEST Flat_Matrix's operators"){
	FlatMatrix<int> m({
		{2, 1},
		{5, 7},
	});
	FlatMatrix<int> m1({
		{4, 1},
		{5, 9},
	});
	FlatMatrix<int> q(m);

	q = 2 + m;
	CHECK(q == m1);

	FlatMatrix<int> mm({
		{2, 1},
		{5, 7},
	});
	FlatMatrix<int> mm1({
		{1, 3},
		{1, 2},
	});
	FlatMatrix<int> mm2({
		{4},
		{6},
	});
	FlatMatrix<int> mm3({
		{1, -2},
		{4, 5},
	});
	FlatMatrix<int> mm4({
		{5, 1},
		{5, 10},
	});
	FlatMatrix<int> mm5({
		{-1, 1},
		{5, 4},
	});
	FlatMatrix<int> mm6({
		{6, 3},
		{15, 21},
	});
    CHECK(mm + mm1 == FlatMatrix<int>({{3, 4}, {6, 9}}));

    CHECK_THROWS_WITH(mm + mm2 == mm3, "invalid argument");
    CHECK_THROWS_WITH(mm - mm2 == mm3, "invalid argument");
    CHECK_THROWS_WITH(mm2 - 1 == mm3, "num_rows must be equal to num_cols");

    CHECK(mm + FlatMatrix<int>({{1, 1}, {2, 2}}) == FlatMatrix<int>({{3, 2}, {7, 9}}));
    CHECK(FlatMatrix<int>({{1, 1}, {2, 2}}) + mm == FlatMatrix<int>({{3, 2}, {7, 9}}));
    CHECK(mm - FlatMatrix<int>({{1, 1}, {2, 2}}) == FlatMatrix<int>({{1, 0}, {3, 5}}));
    CHECK(FlatMatrix<int>({{1, 1}, {2, 2}}) - mm == FlatMatrix<int>({{-1, 0}, {-3, -5}}));
    CHECK(mm - mm1 == mm3);
    CHECK(mm + 3 == mm4);
    CHECK(mm - 3 == mm5);
    CHECK(mm - 3 == mm5);
    CHECK(mm * 3 == mm6);

    CHECK_FALSE(mm == mm1);
    CHECK(mm != mm1);

    FlatMatrix<int> aa({
        {1, 2},
        {3, 4},
        {5, 6},
    });
    FlatMatrix<int> cc({
        {1, 3, 5},
        {2, 4, 6},
    });
    FlatMatrix<int> bb({
        {1, 2},
        {3, 4},
    });
    FlatMatrix<int> j({
        {1},
        {2},
        {3},
    });
    FlatMatrix<int> i({
        {1, 2, 3},
    });


    CHECK(j * i == FlatMatrix<int> ({{1, 2, 3}, {2, 4, 6}, {3, 6, 9}}));
    CHECK(i * j == FlatMatrix<int> ({{14}}));

    m = aa * bb;
    CHECK(m.Row() == 3);
    CHECK(m.Col() == 2);
    CHECK(m == FlatMatrix<int>({{7, 10}, {15, 22}, {23, 34}}));

    m = aa * cc;
    CHECK(m.Row() == 3);
    CHECK(m.Col() == 3);
    CHECK(m.Get(0, 0) == 5);
    CHECK(m.Get(0, 1) == 11);
    CHECK(m.Get(1, 0) == 11);
    CHECK(m.Get(2, 2) == 61);

    CHECK(m == FlatMatrix<int>({{5, 11, 17}, {11, 25, 39}, {17, 39, 61}}));

    FlatMatrix<double> u1({
        {0.5, 0.7},
        {2.5, 2.7},
    });
    FlatMatrix<double> u2({
        {1.5, 1.7},
        {3.5, 3.7},
    });
    CHECK(u1 + FlatMatrix<double>({{1, 1}, {1, 1}}) == u2);
    CHECK(u1 * 2 == FlatMatrix<double>({{1, 1.4}, {5, 5.4}}));
    FlatMatrix<double> u3 = u1 * u2;
    const double eps = 1e5;
    CHECK(abs(u3[0][0] - 3.2) < eps);
    CHECK(abs(u3[0][1] - 3.44) < eps);
    CHECK(abs(u3[1][0] - 13.2) < eps);
    CHECK(abs(u3[1][1] - 14.24) < eps);

}

//------------------------------------------------------------------------------------------------------------

TEST_CASE("TEST Table_Matrix's Get, Row, Col and [ ]"){
    TableMatrix<int> a(5, 6);
    CHECK(a.Get(1, 2) == 0);
    a[0][4] = 1;
    a[0][5] = 1;
    a[1][0] = 1;
    a[0][0] = 10;
    CHECK(a.Get(0, 0) == 10);
    CHECK(a.Get(0, 5) == 1);
    CHECK(a[1][0] == 1);
    CHECK(a[0][0] == 10);
    CHECK(a.Row() == 5);
    CHECK(a.Col() == 6);


    TableMatrix<int> b(2, 2), c(2, 2);
    TableMatrix<int> d({
		{2, 1},
		{5, 7},
	});
	CHECK_THROWS_WITH(TableMatrix<int> e({{2},{5, 7}}), "impossible to create a matrix");
	CHECK(d.Get(0, 0) == 2);
	CHECK(d.Get(0, 1) == 1);
	CHECK(d.Get(1, 0) == 5);
	CHECK(d.Get(1, 1) == 7);

    b[0][0] = 1;
    b[0][1] = 1;
    b[1][0] = 1;
    b[1][1] = 1;
    c[0][0] = 2;
    c[0][1] = 2;
    c[1][0] = 2;
    c[1][1] = 2;
    d = b + c;
    CHECK(d.Row() == 2);
    CHECK((b+c).Col() == 2);
    CHECK((b+c)[0][0] == 3);
    CHECK((b+c)[1][0] == 3);
}

TEST_CASE("TEST Table_Matrix's operators"){
	TableMatrix<int> m({
		{2, 1},
		{5, 7},
	});
	TableMatrix<int> m1({
		{4, 1},
		{5, 9},
	});
	TableMatrix<int> q(m);

	q = 2 + m;
	CHECK(q == m1);

	TableMatrix<int> mm({
		{2, 1},
		{5, 7},
	});
	TableMatrix<int> mm1({
		{1, 3},
		{1, 2},
	});
	TableMatrix<int> mm2({
		{4},
		{6},
	});
	TableMatrix<int> mm3({
		{1, -2},
		{4, 5},
	});
	TableMatrix<int> mm4({
		{5, 1},
		{5, 10},
	});
	TableMatrix<int> mm5({
		{-1, 1},
		{5, 4},
	});
	TableMatrix<int> mm6({
		{6, 3},
		{15, 21},
	});
    CHECK(mm + mm1 == TableMatrix<int>({{3, 4}, {6, 9}}));

    CHECK_THROWS_WITH(mm + mm2 == mm3, "invalid argument");
    CHECK_THROWS_WITH(mm - mm2 == mm3, "invalid argument");
    CHECK_THROWS_WITH(mm2 - 1 == mm3, "num_rows must be equal to num_cols");

    CHECK(mm + TableMatrix<int>({{1, 1}, {2, 2}}) == TableMatrix<int>({{3, 2}, {7, 9}}));
    CHECK(TableMatrix<int>({{1, 1}, {2, 2}}) + mm == TableMatrix<int>({{3, 2}, {7, 9}}));
    CHECK(mm - TableMatrix<int>({{1, 1}, {2, 2}}) == TableMatrix<int>({{1, 0}, {3, 5}}));
    CHECK(TableMatrix<int>({{1, 1}, {2, 2}}) - mm == TableMatrix<int>({{-1, 0}, {-3, -5}}));
    CHECK(mm - mm1 == mm3);
    CHECK(mm + 3 == mm4);
    CHECK(mm - 3 == mm5);
    CHECK(mm - 3 == mm5);
    CHECK(mm * 3 == mm6);

    CHECK_FALSE(mm == mm1);
    CHECK(mm != mm1);

    TableMatrix<int> aa({
        {1, 2},
        {3, 4},
        {5, 6},
    });
    TableMatrix<int> cc({
        {1, 3, 5},
        {2, 4, 6},
    });
    TableMatrix<int> bb({
        {1, 2},
        {3, 4},
    });
    TableMatrix<int> j({
        {1},
        {2},
        {3},
    });
    TableMatrix<int> i({
        {1, 2, 3},
    });

    m = j * i;
    CHECK(m == TableMatrix<int> ({{1, 2, 3}, {2, 4, 6}, {3, 6, 9}}));
    CHECK(i * j == TableMatrix<int> ({{14}}));

    CHECK(j.Col() == 1);
    CHECK(j.Row() == 3);
    CHECK(i.Col() == 3);
    CHECK(i.Row() == 1);
    CHECK(m.Get(0, 0) == 1);
    CHECK(m.Get(0, 1) == 2);
    CHECK(m.Get(0, 2) == 3);
    CHECK(m[1][0] == 2);
    CHECK(m.Get(1, 1) == 4);
    CHECK(m.Get(1, 2) == 6);

    m = aa * bb;
    CHECK(m.Row() == 3);
    CHECK(m.Col() == 2);
    CHECK(m == TableMatrix<int>({{7, 10}, {15, 22}, {23, 34}}));

    m = aa * cc;
    CHECK(m.Row() == 3);
    CHECK(m.Col() == 3);
    CHECK(m.Get(0, 0) == 5);
    CHECK(m.Get(0, 1) == 11);
    CHECK(m.Get(0, 2) == 17);
    CHECK(m.Get(1, 0) == 11);
    CHECK(m.Get(1, 1) == 25);
    CHECK(m.Get(1, 2) == 39);
    CHECK(m.Get(2, 0) == 17);
    CHECK(m.Get(2, 2) == 61);

    CHECK(m == TableMatrix<int>({{5, 11, 17}, {11, 25, 39}, {17, 39, 61}}));

    TableMatrix<double> u1({
        {0.5, 0.7},
        {2.5, 2.7},
    });
    TableMatrix<double> u2({
        {1.5, 1.7},
        {3.5, 3.7},
    });
    CHECK(u1 + TableMatrix<double>({{1, 1}, {1, 1}}) == u2);
    CHECK(u1 * 2 == TableMatrix<double>({{1, 1.4}, {5, 5.4}}));
    TableMatrix<double> u3 = u1 * u2;
    const double eps = 1e5;
    CHECK(abs(u3[0][0] - 3.2) < eps);
    CHECK(abs(u3[0][1] - 3.44) < eps);
    CHECK(abs(u3[1][0] - 13.2) < eps);
    CHECK(abs(u3[1][1] - 14.24) < eps);

}

