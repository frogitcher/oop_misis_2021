#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic.h"
#include <iostream>

TEST_CASE("hell of a test") {
    Dynamic a;
    CHECK(a.Empty());
    CHECK(a.Size() == 0);

    a.push_back(1);

    CHECK_FALSE(a.Empty());
    CHECK(a.Size() == 1);

    //check indexes
    CHECK(a[0] == 1);
    CHECK(a.at(0) == 1);
    CHECK_THROWS_WITH(a.at(3), "You went out of the array");
    CHECK_THROWS_WITH(a[3], "You Fуck");

    Dynamic b({ 1,2,3,4,5 });

    CHECK(b[0]+1==b[4]-b[2]);

    //= != ==
    CHECK(a!=b);

    a = b;

    CHECK(a==b);

    a = { 1,2,3 };
    b = a;

    CHECK(a==b);

    //other
    CHECK(a.Size()==3);

    a.pop_back();

    CHECK(a.Size()==2);

    a.swap(b);

    CHECK(b.Size()==2);
    CHECK(b == Dynamic({1, 2}));
    CHECK(a == Dynamic({ 1,2,3 }));
    CHECK(a.Capacity()>=a.Size());


    a.clear();
    b.clear();

    CHECK(a.Empty());
    CHECK(a.Size() == 0);
    CHECK(a.Capacity() >= a.Size());

    CHECK(a==b);

    Dynamic c(5, 1),e(5);

    CHECK(e == Dynamic({ 0,0,0,0,0 }));
    CHECK(c == Dynamic({ 1,1,1,1,1 }));
    CHECK(c.Size()==5);
    CHECK(c.Size()==e.Size());
    CHECK(Dynamic()==Dynamic(0));

    Dynamic f(5, 3);
    f.resize(7);

    CHECK(f.Size()==7);
    CHECK(f[5]==f[6]);
    CHECK(f[5]==0);
    CHECK(f[4]==3);
    
    f.erase(3);
    f.erase(4);

    CHECK(f[3]==3);
    CHECK(f[4]==0);
    CHECK(f.Size()==5);

    f.insert(4, 10);
    CHECK(f.Size()==6);
    CHECK(f[4]==10);

    f.assign(5, 5);

    CHECK(f.Size()==6);
    CHECK(f[0]==f[4]);
    CHECK(f[0]==5);
}

TEST_CASE("Iterators") {
    Dynamic a;

    CHECK(a.begin() == a.end());

    Dynamic b{ 0,3,6,9 };

    CHECK(b.begin() + b.Size() == b.end());
    CHECK(*b.begin()==0);
    CHECK(*(b.begin()+1) == 3);
}
