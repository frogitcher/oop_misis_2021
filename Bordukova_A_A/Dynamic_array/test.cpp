#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Dynamic.h"

//Create dynamic array
Dynamic_Array a(10, 6);
Dynamic_Array b(5);
Dynamic_Array a_copy(a);
Dynamic_Array d = a;
Dynamic_Array c;
Dynamic_Array e({ 11, 42, 83, 54, 52, 61 });
Dynamic_Array f({ 11, 42, 83, 54, 52, 61 });


TEST_CASE("Testing Creation and Fillability") {
    CHECK(a.Size() == 10);
    CHECK(a[9] == 6);
    CHECK(b[1] == 0);
    CHECK(b.Empty() == false);
    CHECK(b.Capacity() >= b.Size());
    CHECK(c.Size() == 0);
    CHECK(c.begin() == c.Get_Data());
    CHECK(d.Size() == a.Size());
    CHECK(a.Capacity() == a_copy.Capacity());
    CHECK(e[1] == 42);
    std::sort(f.begin(), f.end());
    CHECK(f[2] == 52);
    
}

TEST_CASE("Testing Actions with Array") {
    size_t old_size = a.Size();
    a.push_back(10);
    CHECK(a[10] == 10);
    CHECK(a.end() == a.Get_Data() + a.Size());
    CHECK(a.Size() == old_size + 1);

    a.pop_back();
    CHECK(a.Size() == 10);
    CHECK_THROWS_WITH(c.pop_back(), "Array is empty (there is nothing to delete)!");

    d.clear();
    CHECK(d.Empty());

    CHECK_THROWS_WITH(e.erase(-1), "Index is out of the range!");
    CHECK_THROWS_WITH(e.erase(137), "Index is out of the range!");
    e.erase(3);
    CHECK(e.Size() == 5);
    CHECK(e[3] == 52);

    CHECK_THROWS_WITH(e.insert(456, 4), "Index is out of the range!");
    e.insert(0, 789);
    CHECK(*e.begin() == 789);

    d.resize(37);
    CHECK(d.Size() == 37);
    CHECK(d.end() == d.Get_Data() + d.Size());

    c.assign(3, 947);
    CHECK(c == Dynamic_Array({ 947, 947, 947 }));

    Dynamic_Array one(5, 12);
    Dynamic_Array one_copy(one);
    Dynamic_Array two(7, 53);
    Dynamic_Array two_copy(two);
    two.swap(one);
    CHECK(one_copy == two);
    CHECK(two_copy == one);
}

//They have been also dested in previos cases
TEST_CASE("Testing Pointers") {
    Dynamic_Array one(5, 12);
    Dynamic_Array two(7, 53);
    CHECK(*one.begin() == 12);
    CHECK(two.end() == two.Get_Data() + two.Size());
}

//They have been also dested in previos cases
TEST_CASE("Testing Logical functions") {
    Dynamic_Array one(5, 12);
    Dynamic_Array one_copy(one);
    Dynamic_Array two(7, 53);
    CHECK(one_copy == one);
    CHECK(two != one);
}

TEST_CASE("Testing Assignment") {
    Dynamic_Array one(5, 12);
    one[4] = 924;
    CHECK(one[4] == 924);
}

//They have been also dested in previos cases
TEST_CASE("Testing Indexing and referencing")
{
    Dynamic_Array one(1, 12);
    CHECK_THROWS_WITH(a.at(125), "Index is out of the range!");
    CHECK(a.at(1) == 6);
    CHECK(a[1] == 6);
}
