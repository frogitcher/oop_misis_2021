#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack.h"

TEST_CASE_TEMPLATE("Numbers", T, int, float, double)
{
    std::initializer_list<T> data = { (T)1, (T)2, (T)3, (T)4 };
    Stack<T> a(data);
    Stack<T> b;
    CHECK(a == data);
    CHECK(b.Empty());
    CHECK_FALSE(a.Empty());

    a = b;
    CHECK(a.Empty());
    CHECK(a == b);
    CHECK(a.Size() == 0);
    CHECK(b.Size() == 0);


    Stack<T> c({ (T)2, (T)3, (T)4, (T)5, (T)6, (T)7, (T)1 });
    Stack<T> d({ (T)2, (T)3, (T)4, (T)5, (T)6, (T)7 });
    CHECK(c != d);
    CHECK(c.Size() == 7);
    CHECK(d.Size() == 6);
    c.Pop();
    CHECK(c == d);
    CHECK(c.Size() == 6);
    c.Push((T)1);
    CHECK(c.Size() == 7);


    Stack<T> e(c);
    CHECK(e == c);
    CHECK(e.Size() == c.Size());
    CHECK_FALSE(d == c);

    d.Push((T)1);
    CHECK(d == c);
    CHECK(e == d);
    CHECK(d.Size() == 7);
    e.Pop();
    CHECK(e.Size() == 6);


    Stack<T> ecopy(e);
    CHECK_FALSE(ecopy.Empty());
    CHECK(e == ecopy);
    CHECK(e.Size() == ecopy.Size());
    CHECK_FALSE(ecopy == c);


    Stack<T> y(std::move(e));
    CHECK(e.Empty());
    CHECK(e.Size() == 0);
    CHECK_THROWS_WITH(e.Get(), "there are no elements in the stack");
    CHECK_THROWS_WITH(e.Pop(), "there are no elements in the stack");
    CHECK_FALSE(y.Empty());
    CHECK(y == ecopy);
    CHECK(y.Size() == ecopy.Size());

    Stack <T> f(d);
    CHECK(f.Size() == 7);
    CHECK_FALSE(f.Empty());
    CHECK(f.Get() == (T)1);

    d.Clear();
    CHECK_THROWS_WITH(d.Get(), "there are no elements in the stack");
    CHECK_THROWS_WITH(d.Pop(), "there are no elements in the stack");
    CHECK(d.Size() == 0);
    CHECK(d.Empty());
    for (int i = 0; i < c.Size() - 1; i++){
    f.Pop();
    }
    CHECK(f.Get() == (T)2);
    f.Pop();
    CHECK_THROWS_WITH(f.Pop(), "there are no elements in the stack");
    CHECK_THROWS_WITH(f.Get(), "there are no elements in the stack");
    CHECK(f.Empty());
    CHECK(f.Size() == 0);


    Stack <T> j;
    for (T i = 0; i < 6; i++)
    {
    j.Push(i + (T)2);
    }
    CHECK(j.Size() == 6);
    CHECK(j == ecopy);
}
TEST_CASE("Others") {
    std::initializer_list<bool> data1 = { true, true, false };
    Stack<bool> g(data1);
    CHECK(g.Get() == false);
    CHECK_FALSE(g.Empty());


    std::initializer_list<bool> data2 = { true, true, false, false, true };
    Stack<bool> t(data2);
    CHECK(t.Get() == true);
    CHECK_FALSE(t.Empty());

    g.Merge(t);
    CHECK(g.Size() == 8);
    CHECK(t.Empty());
    CHECK_FALSE(g.Empty());
    CHECK(g.Get() == false);
    int x = 0;
    int z = 0;
    for (int i = 0; i < 8; i++)
    {
        bool y = g.Get();
        CHECK_FALSE(g.Empty());
        if (y == false){ 
            x += 1;} 
        else { 
            z += 1;}
        g.Pop();

    }
    CHECK(x == 3);
    CHECK(z == 5);
    CHECK(g.Empty());

    std::initializer_list<char> data3 = { 'a' , 'b' , 'c' , 'd' };
    std::initializer_list<char> data4 = { 'a', 'b', 'c' };
    Stack s1(data3);
    Stack s2(data4);
    Stack checks1(s1);
    Stack checks2(s2);

    s1.Swap(s2);
    CHECK(s1 == checks2);
    CHECK(s2 == checks1);
    CHECK(s1.Size() == 3);
    CHECK(s2.Size() == 4);

}
