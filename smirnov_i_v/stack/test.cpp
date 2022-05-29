#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <string>
#include "doctest.h"
#include "stack.h"


TEST_CASE("Testing stack") {

	std::initializer_list<int> data = { 5, 3, 6, 2, 9 };

	//default constructor
	Stack<int> st;
	CHECK(st.Size() == 0);
	CHECK(st.GetHead() == nullptr);
	CHECK(st.GetTail() == nullptr);

	//init list constructor
	Stack<int> st1(data);
	Stack<int> st2;
	for (int i : data) {
		st2.Push(i);
	}
	CHECK(st1 == st2);

	//copy constructor
	Stack<int> st3(st1);
	CHECK(st1 == st3);

	//Push
	Stack<int>::Node* tmp = st1.GetHead();
	st1.Push(4);
	CHECK(tmp->value != st1.GetHead()->value);
	CHECK(tmp->value == st1.GetHead()->next->value);

	//Check Pop
	tmp = st1.GetHead()->next;
	st1.Pop();
	CHECK(st1.GetHead()->value == tmp->value);

	//Check Get
	CHECK(st1.Get() == 9);
	st1.Get() = 10;
	CHECK(st1.Get() == 10);

	//Check Empty
	CHECK(st.Empty());
	CHECK(!st1.Empty());

	//Check Size
	CHECK(st.Size() == 0);
	CHECK(st1.Size() == data.size());

	//Check Swap
	int64_t old_size_1 = st1.Size();
	int64_t old_size_3 = st3.Size();
	Stack<int>::Node* old_head_1 = st1.GetHead();
	Stack<int>::Node* old_head_3 = st3.GetHead();
	Stack<int>::Node* old_tail_1 = st1.GetTail();
	Stack<int>::Node* old_tail_3 = st3.GetTail();
	st1.Swap(st3);
	CHECK(st1.Size() == old_size_3);
	CHECK(st3.Size() == old_size_1);
	CHECK(st1.GetHead() == old_head_3);
	CHECK(st3.GetHead() == old_head_1);
	CHECK(st1.GetTail() == old_tail_3);
	CHECK(st3.GetTail() == old_tail_1);

	//Check Merge
	old_head_1 = st1.GetHead();
	old_tail_1 = st1.GetTail();
	old_size_1 = st1.Size();
	old_size_3 = st1.Size();
	st1.Merge(st3);
	CHECK(st1.GetHead() == old_head_3);
	CHECK(st1.GetTail() == old_tail_1);
	CHECK(st1.Size() == old_size_1 + old_size_3);

	//Check operator ==
	Stack<int> stequal(st1);
	Stack<int> stunequal(data);
	CHECK(st1 == stequal);
	CHECK(!(st1 == stunequal));
}