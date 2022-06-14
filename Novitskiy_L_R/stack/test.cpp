#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <string>
#include "doctest.h"
#include "stack.h"


TEST_CASE("Test stack") {
    std::initializer_list<int> data = { 1, 2, 5, 2, 8};

    Stack<int> stack;
    CHECK(stack.Size() == 0);
    CHECK(stack.GetHead() == nullptr);
    CHECK(stack.GetTail() == nullptr);
    Stack<int> stack_1(data);
    Stack<int> stack_2;
    for (int el : data) {
        stack_2.Push(el);
    }
    CHECK(stack_1 == stack_2);

    Stack<int> stack_3(stack_1);
    CHECK(stack_1 == stack_3);

    Stack<int>::Node* node = stack_1.GetHead();
    stack_1.Push(4);
    CHECK(node.value != stack_1.GetHead().value);
    CHECK(node.value == stack_1.GetHead().next.value);

    node = stack_1.GetHead().next;
    stack_1.Pop();
    CHECK(stack_1.GetHead().value == node.value);

    CHECK(stack_1.Get() == 8);
    stack_1.Get() = 100;
    CHECK(stack_1.Get() == 100);

    CHECK(stack.Empty());
    CHECK(!stack_1.Empty());

    CHECK(stack.Size() == 0);
    CHECK(stack_1.Size() == data.size());

    int64_t old_size_1 = stack_1.Size();
    int64_t old_size_3 = stack_3.Size();
    Stack<int>::Node* old_head_1 = stack_1.GetHead();
    Stack<int>::Node* old_tail_1 = stack_1.GetTail();
    Stack<int>::Node* old_tail_3 = stack_3.GetTail();
    stack_1.Swap(stack_3);
    CHECK(stack_1.Size() == old_size_3);
    CHECK(stack_3.Size() == old_size_1);
    CHECK(stack_3.GetHead() == old_head_1);
    CHECK(stack_1.GetTail() == old_tail_3);
    CHECK(stack_3.GetTail() == old_tail_1);

    old_head_1 = stack_1.GetHead();
    old_tail_1 = stack_1.GetTail();
    old_size_1 = stack_1.Size();
    old_size_3 = stack_1.Size();
    stack_1.Merge(stack_3);
    CHECK(stack_1.GetHead() == old_head_3);
    CHECK(stack_1.GetTail() == old_tail_1);
    CHECK(stack_1.Size() == old_size_1 + old_size_3);

    Stack<int> stequal(stack_1);
    Stack<int> stunequal(data);
    CHECK(stack_1 == stequal);
    CHECK(!(stack_1 == stunequal));

}
