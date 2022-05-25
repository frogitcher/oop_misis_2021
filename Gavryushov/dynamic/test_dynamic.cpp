#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic.h"

TEST_CASE("Everything") 
{
    
   DynamicArray a;
   
   CHECK(a.Size() ==0);
   CHECK(a.Empty());
   CHECK(a.Capacity() ==0);
   CHECK_THROWS_WITH(a.pop_back(),"Array is empty");

   DynamicArray b(3);
   CHECK(b.Size()==3);
   CHECK (b.Capacity()>=b.Size());
   DynamicArray c({1,2,3,4});
   CHECK(c.Size()==4);
  DynamicArray d(c);
   CHECK(d.Size()==4);
   CHECK(d.Size()==c.Size());
   CHECK_FALSE(d.Empty());
   for (int i=1;i<5;i++){
       CHECK(c[i-1]==i);
       CHECK(c[i-1]==d[i-1]);
       CHECK(&c[i-1]==(c.begin()+i-1));
   }
   CHECK_THROWS_WITH(d.at(4),"Index out of range");
   CHECK_THROWS_WITH(d.at(-1),"Index out of range");
   CHECK(d.Capacity()==c.Capacity());
   d.push_back(5);
   CHECK(d.Capacity()>=d.Size());
   CHECK(d.Size()==5);
   CHECK(d[4]==5);
   CHECK(&d[4]==d.end()-1);
   int dsize = d.Size();
   int dcapacity = d.Capacity();
   d.Reallocate(20);
   CHECK(dsize == d.Size());
   CHECK(dcapacity <= d.Capacity());
   CHECK(d.Capacity()==20);
   c.push_back(5);
   CHECK(c==d);
   d.pop_back();
   CHECK(d.Size()==dsize-1);
   for (int i=0;i<4;i++){
       CHECK(d[i]==i+1);
   }
   d.clear();
   CHECK(d.Size()==0);
   CHECK(d.Empty());
   c.erase(4);
   for (int i=0;i<4;i++){
       CHECK(c[i]==i+1);
   }
   CHECK(c.Size()==4);
   c.erase(0);
   for (int i=0;i<3;i++){
       CHECK(c[i]==i+2);
   }
   CHECK(c.Size()==3);
   c.erase(1);
   CHECK(c[0]==2);
   CHECK(c[1]==4);

   CHECK_THROWS_WITH(c.erase(2),"Index out of range");
   CHECK_THROWS_WITH(c.erase(-1),"Index out of range");

   c.resize(1);
   CHECK(c.Size()==1);
   CHECK(c[0]==2);
   c.resize(5);
   CHECK(c[0]==2);
   for (int i=1;i<5;i++){
       CHECK(c[i]==0);
   }
   c.resize(0);
   CHECK(c.Empty());
   CHECK_THROWS_WITH(c.resize(-1),"Size must be >=0");
   CHECK_THROWS_WITH(c.assign(-1,5),"Size must be >=0");
   c.assign(3,3);
   for (int i=0;i<3;i++){
       CHECK(c[i]==3);
   }
   c.assign(0,4);
   CHECK(c.Empty());
   CHECK(c.begin()==c.end());
   c.assign(5,5);
   DynamicArray g(c);
   DynamicArray h(d);
   c.swap(d);
   CHECK(c.Size()==h.Size());
   CHECK(d.Size()==g.Size());

   DynamicArray m;
   m.assign(5,5);
   DynamicArray n;
   n.assign(5,4);
   CHECK_FALSE(m==n);
   n.assign(4,5);
   CHECK_FALSE(m==n);
   n.assign(5,5);
   CHECK(m==n);
   DynamicArray k({5,5,5,5,5});
   CHECK(m==k);

   DynamicArray x;
   x = k;
   CHECK(x.Size()==k.Size());
   for (int i=0;i<5;i++){
       CHECK(x[i]==k[i]);
   }

   DynamicArray y;
   x = y;
   CHECK(x==y);
}

