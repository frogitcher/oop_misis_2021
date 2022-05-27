#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "BaseMatrix.h"
#include "FlatMatrix.h"
#include "TableMatrix.h"

TEST_CASE_TEMPLATE("TableMetrix", T, int, int64_t, long, long long, double, float)
{
    CHECK_THROWS_WITH(TableMatrix <T> a(-3, 3, (T)2), "the number of rows of the matrix must be non-negative");
    CHECK_THROWS_WITH(TableMatrix <T> a(-3, -2, (T)2), "the number of rows of the matrix must be non-negative");
    CHECK_THROWS_WITH(TableMatrix <T> a(3, -2, (T)2), "the number of columns of the matrix must be non-negative");
    TableMatrix <T> a(1, 3, (T)2);
    CHECK(a.Get_Number_Cols()==3);
    CHECK(a.Get_Number_Rows()==1);
    CHECK_FALSE(a.Square());
    for (int i=0;i<a.Get_Number_Rows();i++)
    {
        for (int j=0;j<a.Get_Number_Cols();j++)
        {
            CHECK(a[i][j]==T(2));
        }
    }
    TableMatrix <T> b(a); 
    CHECK(b.Get_Number_Cols()==3);
    CHECK(b.Get_Number_Rows()==1);
    CHECK_FALSE(b.Square());
    for (int i=0;i<b.Get_Number_Rows();i++)
    {
        for (int j=0;j<b.Get_Number_Cols();j++)
        {
            CHECK(b[i][j]==T(2));
        }
    }
   CHECK(a==b);
   b.Resize(4, 5, (T)34); 
   CHECK(b.Get_Number_Cols()==5);
   CHECK(b.Get_Number_Rows()==4);
    for (int i=0;i<b.Get_Number_Rows();i++)
    {
        for (int j=0;j<b.Get_Number_Cols();j++)
        {
            CHECK(b[i][j]==T(34));
        }
    }
    CHECK_FALSE(a==b);
    CHECK(a!=b);
    a = b;
    CHECK(a == b);
    CHECK(a.Get_Number_Cols() == b.Get_Number_Cols());
    CHECK(b.Get_Number_Rows() == a.Get_Number_Rows());
    a.Clear();
    CHECK(a.Empty());
    CHECK(a.Get_Number_Cols() == 0);
    CHECK(a.Get_Number_Rows() == 0);
    a.Resize(3, 3);
    CHECK(a.Square());
    TableMatrix<T> c({{(T)34,(T)34,(T)34,(T)34,(T)34}, {(T)34,(T)34,(T)34,(T)34,(T)34}, {(T)34,(T)34,(T)34,(T)34,(T)34}, {(T)34,(T)34,(T)34,(T)34,(T)34}});
    CHECK(c.Get_Number_Cols()==5);
    CHECK(c.Get_Number_Rows()==4);
    CHECK_THROWS_WITH(c.Get(-10,5),"pointer does not match with the size");
    CHECK_THROWS_WITH(c.Get(10,-5),"pointer does not match with the size");
    CHECK(c==b);
    CHECK_THROWS_WITH(TableMatrix<T> d({{(T)34,(T)34,(T)34,(T)34}, {(T)34,(T)34,(T)34,(T)34,(T)34}, {(T)34,(T)34,(T)34,(T)34}, {(T)34,(T)34,(T)34,(T)34,(T)34}}), "such a matrix cannot be created");
    TableMatrix<T> e({{(T)1,(T)2,(T)3}, {(T)4,(T)5,(T)6}, {(T)7,(T)8,(T)9}});
    TableMatrix<T> f({{(T)1,(T)2}, {(T)3,(T)4}, {(T)5,(T)6}});
    CHECK(f.Get_Number_Cols()==2);
    CHECK(f.Get_Number_Rows()==3);
    TableMatrix<T> g({{(T)22,(T)28}, {(T)49,(T)64}, {(T)76,(T)100}});
    TableMatrix<T> h({{(T)23,(T)30}, {(T)52,(T)68}, {(T)81,(T)106}});
    TableMatrix<T> r({{(T)21,(T)26}, {(T)46,(T)60}, {(T)71,(T)94}});
    TableMatrix<T> t=e*f;
    CHECK(t.Get(0,0)==(T)22);
    CHECK(t.Get_Number_Cols()==2);
    CHECK(t.Get_Number_Rows()==3);
    CHECK(t == g);
    TableMatrix<T> l({{(T)1, (T)2,(T)3}});
    TableMatrix<T> m({{(T)4},{(T)5},{(T)6}});
    t = l * m;
    l *= m;
    CHECK(l == t);
    CHECK(t.Get_Number_Cols()==1);
    CHECK(t.Get_Number_Rows()==1);
    CHECK(t.Get(0,0)==(T)32);
    CHECK_THROWS_WITH(t.Get(0,3),"pointer does not match with the size");
    CHECK_THROWS_WITH(t = t * g, "multiplication cannot be performed");
    CHECK_THROWS_WITH(t *= g, "multiplication cannot be performed");
    CHECK_THROWS_WITH(e += f, "addition cannot be performed");
    CHECK_THROWS_WITH(e = e + f, "addition cannot be performed");
    CHECK_THROWS_WITH(e -= f, "subtraction cannot be performed");
    CHECK_THROWS_WITH(e = e - f, "subtraction cannot be performed");
    CHECK(f + g == h);
    TableMatrix<T> fcopy(f);
    fcopy += g;
    CHECK(fcopy == h);
    CHECK(g - f == r);
    g -= f ;
    CHECK(g == r);
    TableMatrix<T> u;
    CHECK(u.Get_Number_Cols() == 0);
    CHECK(u.Get_Number_Rows() == 0);
    CHECK(u.Empty());
    CHECK(u.Square());
}
TEST_CASE_TEMPLATE("FlatMatrix", T, int, int64_t, long, long long, double, float)
{
    CHECK_THROWS_WITH(FlatMatrix <T> a(-3, 3, (T)2), "the number of rows of the matrix must be non-negative");
    CHECK_THROWS_WITH(FlatMatrix <T> a(-3, -2, (T)2), "the number of rows of the matrix must be non-negative");
    CHECK_THROWS_WITH(FlatMatrix <T> a(3, -2, (T)2), "the number of columns of the matrix must be non-negative");
    FlatMatrix <T> a(1, 3, (T)2);
    CHECK(a.Get_Number_Cols()==3);
    CHECK(a.Get_Number_Rows()==1);
    CHECK_FALSE(a.Square());
    for (int i=0;i<a.Get_Number_Rows();i++)
    {
        for (int j=0;j<a.Get_Number_Cols();j++)
        {
            CHECK(a[i][j]==T(2));
        }
    }
    FlatMatrix <T> b(a);
    FlatMatrix<T> w;
    CHECK(b.Get_Number_Cols()==3);
    CHECK(b.Get_Number_Rows()==1);
    CHECK_FALSE(b.Square());
    for (int i=0;i<b.Get_Number_Rows();i++)
    {
        for (int j=0;j<b.Get_Number_Cols();j++)
        {
            CHECK(b[i][j]==T(2));
        }
    }
   CHECK(a==b);
   b.Resize(4, 5, (T)34); 
   CHECK(b.Get_Number_Cols()==5);
   CHECK(b.Get_Number_Rows()==4);
    for (int i=0;i<b.Get_Number_Rows();i++)
    {
        for (int j=0;j<b.Get_Number_Cols();j++)
        {
            CHECK(b[i][j]==T(34));
        }
    }
    CHECK_FALSE(a==b);
    CHECK(a!=b);
    a = b;
    CHECK(a == b);
    CHECK(a.Get_Number_Cols() == b.Get_Number_Cols());
    CHECK(b.Get_Number_Rows() == a.Get_Number_Rows());
    a.Clear();
    CHECK(a.Empty());
    CHECK(a.Get_Number_Cols() == 0);
    CHECK(a.Get_Number_Rows() == 0);
    a.Resize(3, 3);
    CHECK(a.Square());
    FlatMatrix<T> c({{(T)34,(T)34,(T)34,(T)34,(T)34}, {(T)34,(T)34,(T)34,(T)34,(T)34}, {(T)34,(T)34,(T)34,(T)34,(T)34}, {(T)34,(T)34,(T)34,(T)34,(T)34}});
    CHECK(c.Get_Number_Cols()==5);
    CHECK(c.Get_Number_Rows()==4);
    CHECK_THROWS_WITH(c.Get(-10,5),"pointer does not match with the size");
    CHECK_THROWS_WITH(c.Get(10,-5),"pointer does not match with the size");
    CHECK(c==b);
    CHECK_THROWS_WITH(FlatMatrix<T> d({{(T)34,(T)34,(T)34,(T)34}, {(T)34,(T)34,(T)34,(T)34,(T)34}, {(T)34,(T)34,(T)34,(T)34}, {(T)34,(T)34,(T)34,(T)34,(T)34}}), "such a matrix cannot be created");
    FlatMatrix<T> e({{(T)1,(T)2,(T)3}, {(T)4,(T)5,(T)6}, {(T)7,(T)8,(T)9}});
    FlatMatrix<T> f({{(T)1,(T)2}, {(T)3,(T)4}, {(T)5,(T)6}});
    CHECK(f.Get_Number_Cols()==2);
    CHECK(f.Get_Number_Rows()==3);
    FlatMatrix<T> g({{(T)22,(T)28}, {(T)49,(T)64}, {(T)76,(T)100}});
    FlatMatrix<T> h({{(T)23,(T)30}, {(T)52,(T)68}, {(T)81,(T)106}});
    FlatMatrix<T> r({{(T)21,(T)26}, {(T)46,(T)60}, {(T)71,(T)94}});
    FlatMatrix<T> t=e*f;
    CHECK(t.Get(0,0)==(T)22);
    CHECK(t.Get_Number_Cols()==2);
    CHECK(t.Get_Number_Rows()==3);
    CHECK(t == g);
    FlatMatrix<T> l({{(T)1, (T)2,(T)3}});
    FlatMatrix<T> m({{(T)4},{(T)5},{(T)6}});
    t = l * m;
    l *= m;
    CHECK(l == t);
    CHECK(t.Get_Number_Cols()==1);
    CHECK(t.Get_Number_Rows()==1);
    CHECK(t.Get(0,0)==(T)32);
    CHECK_THROWS_WITH(t.Get(0,3),"pointer does not match with the size");
    CHECK_THROWS_WITH(t = t * g, "multiplication cannot be performed");
    CHECK_THROWS_WITH(t *= g, "multiplication cannot be performed");
    CHECK_THROWS_WITH(e += f, "addition cannot be performed");
    CHECK_THROWS_WITH(e = e + f, "addition cannot be performed");
    CHECK_THROWS_WITH(e -= f, "subtraction cannot be performed");
    CHECK_THROWS_WITH(e = e - f, "subtraction cannot be performed");
    CHECK(f + g == h);
    FlatMatrix<T> fcopy(f);
    fcopy += g;
    CHECK(fcopy == h);
    CHECK(g - f == r);
    g -= f ;
    CHECK(g == r);
    FlatMatrix<T> u;
    CHECK(u.Get_Number_Cols() == 0);
    CHECK(u.Get_Number_Rows() == 0);
    CHECK(u.Empty());
    CHECK(u.Square());
    CHECK(0==0);
}