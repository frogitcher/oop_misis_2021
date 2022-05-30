#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack.h"

TEST_CASE_TEMPLATE("Everything", T,int,double,float) 
{
    Stack<T>a({(T)1,(T)2,(T)3,(T)4,(T)5});
    Stack<T> b;
    for (int i=1;i<6;i++){
        b.Push((T)i);
        CHECK(b.Get()==(T)i);
    }
    CHECK(b.Size()==5);
    CHECK(a==b);
    CHECK(a.Get() == (T)5);
    Stack<T> o(a);
    Stack<T> p(o);
    for (int i=5; i>0;i--)
    {
        CHECK(o.Size()==i);
        CHECK(o.Get()==T(i));
        o.Pop();
        CHECK(o.Size()==i-1);
    }
    for (int i=1;i<6;i++){
        o.Push((T)i);
        CHECK(o.Size()==i);
        CHECK(o.Get()==(T)i);
    }

        for (int i=5; i>0;i--)
    {
        CHECK(p.Size()==i);
        CHECK(p.Get()==T(i));
        p.Pop();
        CHECK(p.Size()==i-1);
    }
    for (int i=1;i<6;i++){
        p.Push((T)i);
        CHECK(p.Size()==i);
        CHECK(p.Get()==(T)i);
    }

    CHECK(o.Size()==5);
    CHECK(o.Get() == (T)5);
    for (int i=0;i<5;i++){
        CHECK(o.Get()==p.Get());
        o.Pop();
        p.Pop();
    }
    CHECK(p.Size()==0);
    CHECK(o.Empty());
    CHECK(o==p);
    CHECK_FALSE(o!=p);
    Stack<T> c(a);
    CHECK(c==b);
    c.Pop();
    CHECK(c.Size()==4);
    Stack<T>d( {(T)1,(T)2,(T)3,(T)4} );
    CHECK(c== d);
    c.Clear();
    CHECK(c.Size()==0);
    CHECK_THROWS_WITH(c.Pop(),"Nothing to pop");
    Stack<T>g(c);
    CHECK(g.Empty());
    CHECK(g.Size()==0);
    CHECK_THROWS_WITH(g.Get(),"Stack is empty");
    g.swap(a);
    CHECK(g==b);
    CHECK(a.Empty());
    Stack<T>x( { (T)5,(T)4,(T)3,(T)2,(T)1 });
    Stack<T>f ( { (T)9,(T)8,(T)7,(T)6 } );
    x.merge(f);
    CHECK(x.Size()==9);

    for (int i=1;i<10;i++){
        CHECK(x.Get() == (T)i);
        x.Pop();
    }
    CHECK(f.Empty());
    for (int i=1;i<6;i++){
        f.Push((T)i);
    }
    CHECK(f==b);
    f.Pop();
    f.Push((T)0);
    CHECK(f!=b);
    CHECK_FALSE(f==b);


    Stack<T> z(f);
    Stack<T> y(std::move(f));
    CHECK(f.Empty);
    for (int i=0;i<z.Size();i++){
        CHECK(z.Get()==y.Get());
        z.Pop();
        y.Pop();
    }
 }

