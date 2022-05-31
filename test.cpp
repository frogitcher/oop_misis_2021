#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dyn.h"
TEST_CASE("test all) {
   DynamicArray a(8,5);
   CHECK(a.Size() == 8);
   CHECK(!(a.Empty()));
   CHECK(a[0] == 5);
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
   b.erase(1);
   CHECK(b.Size()==6&&b[2]==4);
   b.insert(1,5);
   CHECK(b.Size()==7&&b[2]==5);
   DynamicArray c(a);
   CHECK(c == a);
   c.assign(3,4);
   CHECK((c.Size()==3)&&(c[2]==4));
   swap c(b);
   CHECK(c!=a);
   CHECK (*(c.begin())==1);
   CHECK (*(c.end())==0);
   c=a;
   CHECK(c==a);
   CHECK_THROWS_WITH(DynamicArray({1,2,3}).at(8),"index out of range");
   CHECK_THROWS_WITH(DynamicArray({}).pop_back(),"array is empty");
   CHECK_THROWS_WITH(DynamicArray({1,2,3}).erase(8),"index out of range");
   CHECK_THROWS_WITH(DynamicArray({1,2,3}).resize(-10),"size cannot be less than zero");
   CHECK_THROWS_WITH(DynamicArray({1,2,3}).insert(4,5),"index out of range");
}
