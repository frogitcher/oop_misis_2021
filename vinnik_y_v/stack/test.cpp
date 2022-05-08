#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Stack.h"

#include <string>

struct human {
    int age;
    std::string name;
};

TEST_CASE("Testing init functions") {
    Stack<int> st1{1, 2};
    Stack<int> st2;
    Stack<std::string> st3{"std", "string"};
    Stack<std::string> st4(st3);
    CHECK(st1 == Stack<int>{1, 2});
    CHECK(st1.Get() == 2);
    CHECK(st1.Size() == 2);
    CHECK(!st1.Empty());
    CHECK(st2.Empty());
    CHECK(st2 == Stack<int>{});
    CHECK(st3.Size() == 2);
    CHECK(st3.Get() == "string");
    CHECK(st4.Get() == "string");
    
    std::vector<Stack<std::string>> vst;
    //Before move
    CHECK(st3 == st4);
    vst.push_back(std::move(st3));
    //After move
    CHECK(st3 != st4);
    CHECK(st4 == vst[0]);
    vst.push_back(std::move(st4));
    CHECK(vst[0] == vst[1]);
    
    //Check if deleting parent stack will lead to child stack having deleted pointers
    Stack<float>* st5 = new Stack<float>{ 1.f, 2.f, 3.05f };
    Stack<float> st6(*st5);
    CHECK(st6 == *st5);
    delete st5;
    CHECK(st6.Get() == 3.05f);
    CHECK(st6.Size() == 3);
    st6.Pop();
    CHECK(st6.Get() == 2.f);
}

TEST_CASE("Testing core stack functionality") {
    Stack<int> st1;
    Stack<int> st2{ 1, 2, 3 };
    Stack<int> st3{ 5, 6 };
    Stack<int> st4{ 4 };

    CHECK(st1.Empty());
    CHECK(st1.Size() == 0);
    CHECK_THROWS_WITH(st1.Pop(), "Cannot pop element from an empty stack");
    CHECK_THROWS_WITH(st1.Get(), "Cannot get element from an empty stack");
    st1.Push(1);
    CHECK(!st1.Empty());
    CHECK(st1.Size() == 1);
    CHECK(st1.Get() == 1);
    st1.Push(-1);
    CHECK(st1 == Stack<int>{1, -1});
    st1.Clear();
    CHECK(st1.Empty());

    CHECK(st2.Get() == 3);
    CHECK(st2.Size() == 3);
    CHECK(st4.Get() == 4);
    st4.Merge(st3);
    CHECK(st4.Size() == 3);
    CHECK(st4 == Stack<int>{4, 5, 6});
    st2.Swap(st4);
    CHECK(st4 == Stack<int>{1, 2, 3});
    CHECK(st2 == Stack<int>{4, 5, 6});
    st4.Merge(st2);
    CHECK(st4 == Stack<int>{1, 2, 3, 4, 5, 6});
    st4.Clear();
    CHECK(st4.Empty());

    //Check if deleting stack object after merging/swapping is safe
    Stack<human>* st_ptr1 = new Stack<human>{ human{56, "Joe"}, human{43, "Suzy"} };
    Stack<human>* st_ptr2 = new Stack<human>{ human{22, "David"}, human{34, "Jeff"} };
    Stack<human>* st_ptr3 = new Stack<human>{};
    CHECK(st_ptr1->Get().name == "Suzy");
    CHECK(st_ptr2->Get().name == "Jeff");
    CHECK(st_ptr3->Empty());

    st_ptr3->Merge(*st_ptr1);
    CHECK(st_ptr3->Size() == 2);
    CHECK(st_ptr3->Get().name == "Suzy");
    delete st_ptr1;
    CHECK(st_ptr3->Get().name == "Suzy");
    st_ptr3->Swap(*st_ptr2);
    CHECK(st_ptr3->Get().name == "Jeff");
    delete st_ptr2;
    CHECK(st_ptr3->Get().name == "Jeff");
}

TEST_CASE("Testing additional stack operators") {
    //Testing = operator
    Stack<int> _st1 = {1, 4};
    CHECK(_st1 == Stack<int>{1, 4});
    Stack<int> _st2 = { 0 };
    _st1 = _st2;
    CHECK(_st1 == _st2);

    //Testring + and += operators
    Stack<std::string> st1{ "Can", "I" };
    Stack<std::string> st2{ "get" };
    Stack<std::string> st3{ "an approve" };
    Stack<std::string> st4{ "please?" };
    Stack<std::string> st5 = st1 + st2 + st3;
    CHECK(st5 == Stack<std::string>{"Can", "I", "get", "an approve"});
    //Gotta say please
    st5 += st4;
    CHECK(st5.Get() == "please?");
    CHECK(st5 == Stack<std::string>{"Can", "I", "get", "an approve", "please?"});

    //Testing != operator (just in case)
    Stack<unsigned long long> st6 = { 1, 2 };
    Stack<unsigned long long> st7 = { 3, 1 };
    Stack<unsigned long long> st8;
    CHECK(st6 != st7);
    CHECK(st6 != st8);
}
