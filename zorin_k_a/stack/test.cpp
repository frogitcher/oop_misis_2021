#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack.h"
#include <string>
#include "stack.cpp"
TEST_CASE("testing the factorial function")
{
    Stack<int> a({1,2,3,4,5});
    Stack<double> b;
    Stack<int> c({3,4,5});

    CHECK(a.Size() == 5);

    CHECK(b.Empty());
    b.Push(1.5);
    CHECK(b.Get()==1.5);
    CHECK(c!=a);

    c.Pop();
    CHECK(c.Size()==2);

    b.Clear();
    CHECK_THROWS_WITH(b.Get(),"Stack is empty");
    CHECK_THROWS_WITH(b.Pop(),"stack is already empty");

    a.Swap(c);
    CHECK(a.Size()==2);

    Stack<int> d {1, 8};
	a.Merge(d);
	CHECK(a.Size() == 4);
	CHECK(d.Size() == 0);
}
