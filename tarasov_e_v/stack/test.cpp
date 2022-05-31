//
// Created by Егор Тарасов on 5/28/22.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <initializer_list>

#include "doctest.h"
#include "stack.h"

TEST_CASE_TEMPLATE("Testing constructors", T, double, long long,
                   unsigned long long) {
    stack<T> a;
    CHECK(a.Size() == 0);
    CHECK(a.empty());

    stack<T> b(a);
    CHECK(b.Size() == a.Size());
    CHECK(b.empty());
    stack<T> c = (std::initializer_list<T>{(T) 6.3f, (T) -3, 3, 0});
    CHECK(c.Size() == 4);
}

TEST_CASE_TEMPLATE("Testing \"pop\",\"push\", \"get\"", T, double, long long,
                   unsigned long long) {
    stack<T> a;
    a.push((T) 6.3f);
    CHECK(a.Size() == 1);
    CHECK(a.get() == (T) 6.3f);

    a.pop();
    CHECK(a.Size() == 0);
    CHECK_THROWS_WITH(a.get(), "stack is empty!");
    CHECK_THROWS_WITH(a.pop(), "stack is empty!");
}

TEST_CASE_TEMPLATE("Testing additional function \"swap\"", T, double, long long,
                   unsigned long long) {
    stack<T> a(std::initializer_list<T>{(T) 4.5f, (T) 5, (T) 3});
    stack<T> b(std::initializer_list<T>{(T) 1.4f, (T) 2});
    stack<T> buffer1 = b;
    stack<T> buffer2 = a;
    b.swap(a);
    CHECK(b.Size() == 3);
    CHECK(a.Size() == 2);
    CHECK((a != buffer2));
    CHECK((b != buffer1));
    CHECK((a == buffer1));
    CHECK((b == buffer2));
}

TEST_CASE_TEMPLATE("Testing additional function \"merge\"", T, double,
                   long long, unsigned long long) {
    stack<T> a(std::initializer_list<T>{(T) 4.5f, (T) 5});
    stack<T> b(std::initializer_list<T>{(T) 1.4f, (T) 2});
    a.merge(b);
    CHECK(a.Size() == 4);
    CHECK((a == stack<T>(std::initializer_list<T>{(T) 1.4f, (T) 2, (T) 4.5f, (T) 5})));
    CHECK(b.Size() == 0);
}

TEST_CASE_TEMPLATE("Testing boolean operators", T, int, double, long long,
                   unsigned long long) {
    stack<T> a;
    stack<T> b;
    CHECK((a == b));
    a.push((T) 1);
    CHECK((a != b));
    CHECK_FALSE((a == b));
}