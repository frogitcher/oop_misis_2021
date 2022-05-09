#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic_array.h"

TEST_CASE("Constructors") 
{
    DynamicArray a;

    CHECK(a.Size() == 0);
    CHECK(a.Empty());

    DynamicArray b(10);
    CHECK(b.Size() == 10);
    CHECK_FALSE(b.Empty());
    CHECK_FALSE(b.Size() ==666);
    CHECK(b.Capacity() >= b.Size());


    DynamicArray c(b);
    CHECK(b.Size() == c.Size());
    CHECK_FALSE(c.Empty());
    CHECK(b.Capacity() == c.Capacity());
    for (int64_t i = 0; i < b.Size(); i++)
    {
        CHECK (b[i] == c[i]);
    }
    CHECK(b == c);


    DynamicArray d({1,2,3,4,5,6,7,9,10});
    CHECK(d.Size()==9);
    CHECK_FALSE(d.Empty());
    CHECK(d.Capacity() >= d.Size());
    CHECK_FALSE(d==b);
    CHECK(d[0]==1);
    CHECK(d[1]==2);
    CHECK(d[2]==3);
    CHECK(d[3]==4);
    CHECK(d[4]==5);
    CHECK(d[5]==6);
    CHECK(d[6]==7);
    CHECK_FALSE(d[7]==8);
    CHECK(d[7]==9);
    CHECK(d[8]==10);
}
TEST_CASE("Operators") 
{
    DynamicArray a({1,2,3}); 
 for (int64_t i = 0; i < a.Size(); i++)
    {
        CHECK(&(a[i]) == (a.begin() + i));
    }
    CHECK_THROWS_WITH(a.at(3), "the pointer does not match the size of the array");
    CHECK(a.at(0) == 1);

}
TEST_CASE("Methods") 
{
    DynamicArray a({1,2,3});
    int64_t s = a.Size();
    a.push_back(4);
    CHECK(a.Size() == s + 1);
    CHECK(a.Capacity() >= a.Size());
    CHECK(a[0]==1);
    CHECK(a[1]==2);
    CHECK(a[2]==3);
    CHECK(a[3]==4);

    s = a.Size();
    a.reallocate(40);
    CHECK(a.Capacity()>=s);
    CHECK(a.Size()==s);
    a.reallocate(0);
    CHECK(a.Capacity()>=s);


    DynamicArray b{0,1};
    s = b.Size();
    b.pop_back();
    CHECK(b[0]==0);
    b.pop_back();
    CHECK(b.Size() == s - 2);
    CHECK_THROWS_WITH(b.pop_back(), "there are no elements in the array");
   
    DynamicArray c({1,2,3,4,5,6,7,8,9}); 
    s = c.Size();
    c.erase(3);
    CHECK(c.Size() == s - 1);
    CHECK(c[0]==1);
    CHECK(c[1]==2);
    CHECK(c[2]==3);
    CHECK_FALSE(c[3]==4);
    CHECK(c[3]==5);
    CHECK(c[4]==6);
    CHECK(c[5]==7);
    CHECK(c[6]==8);
    CHECK(c[7]==9);
    s = c.Size();
    c.erase(c.Size()-1);
    CHECK(c.Size() == s - 1);
    CHECK(c[0]==1);
    CHECK(c[1]==2);
    CHECK(c[2]==3);
    CHECK(c[3]==5);
    CHECK(c[4]==6);
    CHECK(c[5]==7);
    CHECK(c[6]==8);
    CHECK_THROWS_WITH(c.at(7), "the pointer does not match the size of the array");
    
    c.clear();
    CHECK(c.Size()==0);
    CHECK_THROWS_WITH(c.at(0), "the pointer does not match the size of the array");

    c.reallocate(0);
    c.resize(5);
    CHECK(c.Size() == 5);
    CHECK(c.Capacity() >= c.Size());
    for (int64_t i = 0; i < c.Size(); i++)
    {
     CHECK(c[i] == 0);   
    }
    DynamicArray d({1,2,3});
    d.resize(4);
    CHECK(d.Size() == 4);
    CHECK(d[0]==1);
    CHECK(d[1]==2);
    CHECK(d[2]==3);
    CHECK(d[3]==0);
    d.resize(2);
    CHECK(d.Size() == 2);
    CHECK(d[0]==1);
    CHECK(d[1]==2);
    CHECK_THROWS_WITH(d.at(3), "the pointer does not match the size of the array");
    d.resize(0);
    CHECK(d.Size() == 0);
    CHECK(d.Empty());
    CHECK_THROWS_WITH(d.at(3), "the pointer does not match the size of the array");
    CHECK_THROWS_WITH(d.resize(-100), "the size of the array must be non-negative");

    d.assign(5,3);
    CHECK(d.Size() == 5);
    for (int64_t i = 0; i < d.Size(); i++)
    {
     CHECK(d[i] == 3);   
    }
    CHECK_THROWS_WITH(d.assign(-100,8), "the size of the array must be non-negative");
    d.assign(0,3);
    CHECK(d.Size() == 0);
    CHECK(d.Empty());
    
    CHECK(d.end() == d.GetData());
    CHECK(d.begin() == d.GetData());

    DynamicArray e({7,8,9});
    CHECK(*(e.end()-1) == 9);
    CHECK(*(e.begin()) == 7);
    DynamicArray f({7,8,9});
    DynamicArray g({1,2,3,4,5});
    CHECK(e==f);
    CHECK_FALSE(g==f);
    CHECK(g!=f);
    CHECK_FALSE(e!=f);
    s=g.Size();
    int64_t s1=f.Size();
    g.swap(f);
    CHECK(g[0]==7);
    CHECK(g[1]==8);
    CHECK(g[2]==9);
    CHECK(g==e);
    e=f;
    CHECK(g!=e);
    CHECK(s==f.Size());
    CHECK(s1==g.Size());
    s=g.Size();
    g.insert(3,1);
    CHECK(g.Size()==s+1);
    CHECK(g[0]==7);
    CHECK(g[1]==8);
    CHECK(g[2]==9);
    CHECK(g[3]==1);
    CHECK_THROWS_WITH(g.insert(-300,1), "the pointer does not match the size of the array");
    CHECK_THROWS_WITH(g.insert(50,1), "the pointer does not match the size of the array");
    s=g.Size();
    g.insert(0,6);
    CHECK(g.Size()==s+1);
    CHECK(g[0]==6);
    CHECK(g[1]==7);
    CHECK(g[2]==8);
    CHECK(g[3]==9);
    CHECK(g[4]==1);
    s=g.Size();
    g.insert(3,5);
    CHECK(g.Size()==s+1);
    CHECK(g[0]==6);
    CHECK(g[1]==7);
    CHECK(g[2]==8);
    CHECK(g[3]==5);
    CHECK(g[4]==9);
    CHECK(g[5]==1);

}
