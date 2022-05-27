#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "stack.h"
#include "doctest.h"
#include <string>
TEST_CASE("Declarations") {

    Stack<int> a;
    CHECK(a.Empty() == 1);
    CHECK_THROWS_WITH(a.Get(), "You went out of the stack");
    CHECK_THROWS_WITH(a.Pop(), "You went out of the stack");

    Stack<int> b{ 0,1,2,3,4 };
    CHECK(b.Size() == 5);
    for (int i = 4;i >= 0;i--) {
        CHECK(b.Get() == i);
        b.Pop();
    }
    CHECK(b.Size() == 0);
    for (int i = 4;i >= 0;i--) {
        b.Push(i);
        CHECK(b.Get() == i);
    }
    CHECK(b.Size() == 5);
    auto c = &b;
    CHECK(c->Get() == 0);
    b.Del();
    CHECK(c->Get() != 0); //ïðîâåðêà î÷èñòêè ïàìÿòè
    CHECK(b.Empty() == 0);
    a.Del();
}

TEST_CASE("Operators") {

    Stack<double> s({ 1.0,2.0,3.0 });
    Stack<double> o;
    CHECK(s.Size() == 3);
    CHECK(s != o);
    o = s;
    CHECK(s == o);
}

TEST_CASE("Other Declarations") {
    Stack<long long> s({ 1,2,3 });
    Stack<long long> o;
    CHECK(s.Size() == 3);
    CHECK(s != o);
    o = s;
    CHECK(s == o);
}

TEST_CASE("Other") {
    Stack<int>a({ 3,4,5,6 });
    Stack<int>b({ 7,8 });
    a.merge(b);
    CHECK(a.size == 6);
    for (int i = 8;i > 2;i--) {
        CHECK(a.Get() == i);
        a.Pop();
    }
    CHECK(a.Size() == 0);
    CHECK(b.Size() == 0);

    Stack<int> e({ 0,0,0 });
    Stack<int> c({ 1,1 });
    e.Swap(c);
    CHECK(e.Size() == 2);
    CHECK(c.Size() == 3);
    CHECK(e.Get() == 1);
    CHECK(c.Get() == 0);

}


