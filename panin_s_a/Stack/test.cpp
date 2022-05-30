#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Stack.h"
#include <string>
#include <iostream>
using std::cout;
// using namespace std;

TEST_CASE("a") {
    Stack<int> a1{1,2,3,4,5}, a2{6,5,4,3,2,1}, a3{1,2,3,4,5}, a;
    SUBCASE("Testing constructors and clear")
    {
        CHECK(a.Size() == 0);
        for (int i = 1; i <= 6; i++)
        {
            CHECK(a2.Get() == i);
            a2.Pop();
        }
        Stack<int> a4(a1);
        for (int i = 5; i >= 1; i--)
        {
            CHECK(a4.Get() == i);
            a4.Pop();
        }
        Stack<int> a5(std::move(Stack<int>{6,5,4,3,2,1}));
        for (int i = 1; i <= 6; i++)
        {
            CHECK(a5.Get() == i);
            a5.Pop();
        }
    }
}

TEST_CASE("b") {
    Stack<int> s, s1{2,2,2}, s2{2,2,2}, s3{3,2,1};
    SUBCASE("Testing push and pop get size empty swap")
    {
        s.Push(1);
        s.Push(2);
        s.Push(3);
        for (int i = 3; i >= 1; i--)
        {
            CHECK(s.Get() == i);
            s.Pop();
        }
        CHECK(s.Empty());
        CHECK(s.Size() == 0);
        CHECK_THROWS_WITH(s.Pop(), "trying pop from empty stack");
        s.Push(1);
        s.Push(1);
        s.Push(1);
        s.Push(1);
        s.Push(1);
        CHECK(s.Size() == 5);
        s1.Swap(s3);
        for (int i = 1; i >= 3; i++)
        {
            CHECK(s1.Get() == i);
            s1.Pop();
        }
        for (int i = 0; i < 3; i++)
        {
            CHECK(s2.Get() == 2);
            s2.Pop();
        }
    }
}

TEST_CASE("c") {
    Stack<int> s1{1,2,3}, s2{4,5,6}, s3{1,2,3}, s4{4,5,6}, s5{};
    SUBCASE("Testing merge"){
        s1.Merge(s2);
        for (int i = 6; i >= 1; i--)
        {
            CHECK(s1.Get() == i);
            s1.Pop();
        }
        CHECK(s2.Size() == 0);
        CHECK(s1.Size() == 0);
        s1.Merge(s3);
        CHECK(s1.Size() == 3);
        s1.Merge(s4);
        CHECK(s1.Size() == 6);
        s1.Merge(s5);
        for (int i = 6; i >= 1; i--)
        {
            CHECK(s1.Get() == i);
            s1.Pop();
        }
    }
}

TEST_CASE("D") {
    Stack<int> s1{1,1,1,1}, s2{1,1,1}, s3{1,1,1,1}, s4{1,20,3,4}, s5{1,20,3,4};
    SUBCASE("Testing Clear == !="){
        CHECK((s1 == s3));
        CHECK((s4 == s5));
        CHECK((s1 != s2));
        CHECK((s4 != s3));
        for (int i = 0; i < 4; i++)
        {
            CHECK(s1.Get() == 1);
            s1.Pop();
            CHECK(s3.Get() == 1);
            s3.Pop();
        }
        for (int i = 0; i < 3; i++)
        {
            CHECK(s2.Get() == 1);
            s2.Pop();
        }
        CHECK(s4.Get() == 4);
        s4.Pop();
        CHECK(s4.Get() == 3);
        s4.Pop();
        CHECK(s4.Get() == 20);
        s4.Pop();
        CHECK(s4.Get() == 1);
        s4.Pop();
        CHECK(s4.Empty());
        CHECK(s5.Size() == 4);
        s5.Clear();
        CHECK(s5.Empty());
    }
    Stack<int> s10, s11{9,1,1}, s12;
    SUBCASE("Testing ="){
        s10 = s11;
        CHECK((s10 == s11));
        CHECK((s11 == std::move(Stack<int>{9,1,1})));
        s11.Clear();
        CHECK((s10 == std::move(Stack<int>{9,1,1})));

    }
}
