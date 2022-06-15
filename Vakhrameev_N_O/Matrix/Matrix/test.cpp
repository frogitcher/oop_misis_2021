#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "class_matrix.h"
#include "class_flat_matrix.h"
#include "class_table_matrix.h"
template<typename T>
void print(FlatMatrix<T>& other)
{
    for (int i=0;i<other.get_rows();i++)
    {
        for (int j=0;j<other.get_columns();j++)
        {
            std::cout<<other.Get(i,j)<<" ";
        }
        std::cout<<std::endl;
    }
}
template<typename T>
void Print(TableMatrix<T>& other)
{
    for  (int i=0;i<other.get_rows();i++)
    {
        for (int j=0;j<other.get_columns();j++)
        {
            std::cout<<other.Get(i,j)<<" ";
        }
        std::cout<<std::endl;
    }
}
TEST_CASE("Testing FlatMatrix")
{
    FlatMatrix<int> b(1,3,6);
    FlatMatrix<int> b_clone(b);
    FlatMatrix<int> a({{1,2,3,4},{4,3,2,1}});
    FlatMatrix<int> c(2,2,3);
    for (int i=0;i<b.get_rows();i++)
    {
        for (int j=0;j<b.get_columns();j++)
        {
            b[i][j]=1;
        }
    }
    print(b);

    b.resize(4,4,5);

    print(b);

    print(b_clone);

    print(a);

    print(c);

    b+=3;
    print(b);

    b-=3;
    print(b);

    b*=3;
    print(b);

    b_clone.diag(b.get_rows(),1);
    b*=b_clone;
    print(b);
    print(b_clone);

    c=b;
    c-=b_clone;
    print(c);
    c+=b_clone;
    print(b);
    print(c);
    std::cout<<c.get_rows()<<" "<<c.get_columns()<<" "<<b.get_rows()<<" "<<b.get_columns()<<std::endl;
    CHECK(c==b);
    CHECK((b!=c)==false);
    CHECK((b!=a));
    CHECK_THROWS_WITH(FlatMatrix<int> x({{1,2,3},{1,2}}),"rows in intitalizer list should have the same size");
    CHECK_THROWS_WITH(c.Get(4,4),"indexes are out of range!");
    CHECK_THROWS_WITH(a+=b,"sizes of matrixes are not equal");
    CHECK_THROWS_WITH(a+b,"sizes of matrixes are not equal");
}

TEST_CASE("Testing TableMatrix")
{
    TableMatrix<int> b(1,3,6);
    TableMatrix<int> b_clone(b);
    TableMatrix<int> a({{1,2,3,4},{4,3,2,1}});
    TableMatrix<int> c(2,2,3);
    TableMatrix<int> t(b);
    Print(b);
    for (int i=0;i<b.get_rows();i++)
    {
        for (int j=0;j<b.get_columns();j++)
        {
            b[i][j]=1;
        }
    }
    Print(b);

    b.resize(4,4,5);

    Print(b);

    Print(b_clone);

    Print(a);

    Print(c);

    b+=3;
    Print(b);

    b-=3;
    Print(b);

    b*=3;
    Print(b);

    b_clone.diag(b.get_rows(),1);
    b*=b_clone;
    Print(b);
    Print(b_clone);
    c=b;
    c-=b_clone;
    Print(c);
    c+=b_clone;
    std::cout<<std::endl;
    Print(c);
    std::cout<<c.get_rows()<<" "<<c.get_columns()<<" "<<b.get_rows()<<" "<<b.get_columns()<<std::endl;
    CHECK(c==b);
    CHECK((b!=c)==false);
    CHECK((b!=a));
    CHECK_THROWS_WITH(TableMatrix<int> x({{1,2,3},{1,2}}),"rows in intitalizer list should have the same size");
    CHECK_THROWS_WITH(c.Get(4,4),"indexes are out of range");
    CHECK_THROWS_WITH(a+=b,"sizes of matrixes are not equal");
    CHECK_THROWS_WITH(a+b,"sizes of matrixes are not equal");
    CHECK_THROWS_WITH(a+3,"matrix sholud be squre to do this operation");
}
