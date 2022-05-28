#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "class_stack.h"
std::initializer_list<int> list={1,2,3,4,5,6};
Stack<int> example1(list);
Stack<int> example2(example1);
Stack<int> example3;
TEST_CASE("testing stack")
{
    CHECK(example1.Empty()==false);
    for (auto& i:list)
    {
        example3.Push(i);
    }
    CHECK(example1.Size()!=0);
    CHECK(example1==example2);
    CHECK(example2==example3);
}

TEST_CASE("testing functions and boolean operators")
{
    example1.Pop();
    CHECK(example1!=example2);
    CHECK((example1==example2)==false);
    example2.Pop();
    CHECK(example1.Get()==example2.Get());
    CHECK(example1.Size()==example2.Size());
    example1.Push(6);
    example2.Swap(example1);
    CHECK(example2==example3);
    example1.Merge(example2);
    CHECK(example1.Size()==11);
    std::string s="";
    while(!example1.Empty())
    {
        s+=std::to_string(example1.Get());
        example1.Pop();

    }
    CHECK(s=="54321654321");
    example1=example3;
    s="";
    while(!example1.Empty())
    {
        s+=std::to_string(example1.Get());
        example1.Pop();

    }
    CHECK(s=="654321");
}

TEST_CASE("testing exceptions")
{
    CHECK_THROWS_WITH(example1.Pop(),"stack contains no attributes" );
    CHECK_THROWS_WITH(example1.Get(),"Size is equal to zero");
}
