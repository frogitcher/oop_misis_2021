#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "class_dynamic_array.h"
Dynamic_array a(0);
Dynamic_array b(3, 5);
Dynamic_array c(3, 0);
Dynamic_array b_copy = b;
Dynamic_array c_copy = c;
Dynamic_array d(3, 0);
Dynamic_array e({ 1,2,3 });
TEST_CASE("testing output")
{
    /*for (int i = 0;i < b.Size();i++)
    {
        std::cout << b[i] << " ";
    }*/
    std::cout << b;
    std::cout << b.Size() << std::endl;
    for (int i = 0;i < e.Size();i++)
    {
        std::cout << e[i] << " ";
    }
    std::cout << std::endl;
}

TEST_CASE("testing editing/boolean functions")
{
    a.push_back(1);
    CHECK(a == Dynamic_array(1, 1));
    CHECK(a != b);
    b.swap(c);
    CHECK(b == c_copy);
    CHECK(c == b_copy);
    b.swap(c);
    b.pop_back();
    CHECK(b == Dynamic_array(2, 5));
    CHECK(a < b);
    CHECK(a <= b);
    CHECK(b > a);
    CHECK(b >= a);
    CHECK(a != b);
    a.assign(3, 0);
    CHECK(a == c);
    a.erase(1);
    CHECK(a == Dynamic_array(2, 0));
    CHECK(Dynamic_array(0).Empty() == true);
    c.clear();
    CHECK(c.Capacity() == 6);
}

TEST_CASE("testing exceptions")
{
    a.assign(0);
    CHECK_THROWS_WITH(a.pop_back(), "Dynamic array has no elements!");
    CHECK_THROWS_WITH(a.erase(1), "impossible to erase element that is out of array range");
}
