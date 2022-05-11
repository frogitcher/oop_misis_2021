#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic.h"

TEST_CASE("testing the constructors") {
   DynamicArray a(5,3);
   CHECK(a.Size() == 5);
   CHECK(!(a.Empty()));
   CHECK(a[0] == 3);
   a.clear();
   CHECK(a.Empty());

   DynamicArray b({1,2,3,4,5});
   CHECK(b[0] == 1);
   CHECK(b[3] == 4);
   CHECK(b.Size()==5);
   b.push_back(6);
   CHECK(b[5]==6);
   b.pop_back();
   CHECK(b.Size()==5);
   b.resize(7);
   CHECK(b.Size()==7);
   b.erase(2);
   CHECK(b.Size()==6&&b[2]==4);
   b.insert(2,5);
   CHECK(b.Size()==7&&b[2]==5);

   DynamicArray c(a);
   CHECK(c == a);
   c.assign(2,5);
   CHECK((c.Size()==2)&&(c[2]==5));
   swap c(b);
   CHECK(c!=a);
   CHECK (*(c.begin())==1);
   CHECK (*(c.end())==0);
   c=b;
   CHECK(c==a);

   CHECK_THROWS_WITH(DynamicArray({1,2,3}).at(6),"index out of range");
   CHECK_THROWS_WITH(DynamicArray({}).pop_back(),"Array is empty");
   CHECK_THROWS_WITH(DynamicArray({1,2,3}).erase(6),"Index out of range");
   CHECK_THROWS_WITH(DynamicArray({1,2,3}).resize(-5),"size must be > 0");
   CHECK_THROWS_WITH(DynamicArray({1,2,3}).insert(4,10),"index doesn't match the array's size");
   CHECK_THROWS_WITH(DynamicArray({1,2,3}).assign(4,5),"size must be > 0");
}
