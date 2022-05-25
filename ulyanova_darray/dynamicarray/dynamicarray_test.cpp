#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "dynamicarray.h"
#include "doctest.h"

TEST_CASE("Empty Constructor Testing") {

	DynamicArray x;
	CHECK(x.Size() == 0);
	CHECK(x.Capacity() == 0);
	CHECK(x.begin() == x.end());
	CHECK(x.Empty());
	CHECK((x == DynamicArray()));
	CHECK((x.Size() == 3) == false);
}

TEST_CASE("Constructor Testing") {

	DynamicArray y(10);
	CHECK(y.Size() == 10);
	CHECK(y.Capacity() >= y.Size());
	for (int64_t t : y) {
		CHECK(t == 0);
	}

	DynamicArray x(15, 3);
	CHECK(x.Size() == 15);
	CHECK(x.Capacity() >= x.Size());
	for (int64_t t : x) {
		CHECK(t == 3);
	}

	CHECK_THROWS(DynamicArray(-10));
	CHECK_THROWS(DynamicArray(-5, 5));

}

TEST_CASE("Other Constructor Testing") {

	DynamicArray x(5, 1);
	DynamicArray y(x);
	CHECK(x.Size() == y.Size());
	CHECK(x.Capacity() == y.Capacity());
	for (int64_t i = 0; i < x.Size(); i++) {
		CHECK(x[i] == y[i]);
	}

	DynamicArray p = { 1, 2, 3 };
	DynamicArray q(p);
	CHECK(p.Size() == q.Size());
	CHECK(p.Capacity() == q.Capacity());
	for (int64_t i = 0; i < p.Size(); i++) {
		CHECK(p[i] == q[i]);
	}

	DynamicArray k;
	DynamicArray n(k);
	CHECK(k.Size() == n.Size());
	CHECK(k.Capacity() == n.Capacity());
	CHECK(k.Empty());
	CHECK(n.Empty());
}

TEST_CASE("Index [] At Testing") {

	DynamicArray x(10, 3);

	for (int64_t i = 0; i < x.Size(); i++) {

		CHECK(&(x[i]) == (x.GetData() + i));
		CHECK(x[i] == 3);
		CHECK(&(x.At(i)) == &(x[i]));
		CHECK(&(x.At(i)) == (x.GetData() + i));
		CHECK((x.At(i)) == 3);
		CHECK(&(x.At(i)) == (x.begin() + i));
		CHECK(&(x[i]) == (x.begin() + i));
		CHECK(((x[i] == 5) && (x.At(i) == 5)) == false);
	}

	CHECK_THROWS(x.At(11));
	CHECK_THROWS(x.At(x.Size()));
	CHECK_THROWS(x.At(-100));
}

TEST_CASE("Empty Testing") {

	CHECK(DynamicArray().Empty() == true);
	CHECK(DynamicArray(0, 1).Empty() == true);
	CHECK(DynamicArray(3, 4).Empty() == false);
	CHECK(DynamicArray(7).Empty() == false);
	CHECK(DynamicArray({ 1,2,3,4,5 }).Empty() == false);
	CHECK(DynamicArray({}).Empty() == true);
}

TEST_CASE("Push Back Testing") {

	DynamicArray x{ 2, 3, 1, 9, 11, 50 };
	DynamicArray y(x);
	int64_t s = x.Size();
	int64_t c = x.Capacity();
	x.Push_back(3);

	CHECK(x.Size() == s + 1);
	CHECK(x[s] == 3);
	CHECK(x[x.Size() - 1] == 3);
	CHECK(x.Capacity() == c * 2);

	for (int64_t i = 0; i < y.Size(); i++) {
		CHECK(x[i] == y[i]);
	}
	
	DynamicArray a;
	a.Push_back(1);
	CHECK(a.Empty() == false);
	CHECK(a.Size() == 1);
	CHECK(a.Capacity() == 1);
	CHECK(a[0] == 1);
}

TEST_CASE("Pop Back Testing") {

	DynamicArray x{2, 3, 1, 9, 11, 50};
	DynamicArray y(x);
	int64_t s = x.Size();
	int64_t c = x.Capacity();
	x.Pop_back();

	CHECK(s - 1 == x.Size());
	for (int64_t i = 0; i < x.Size(); i++) {
		CHECK(x[i] == y[i]);
	}

	DynamicArray k = { 1 };
	k.Pop_back();
	CHECK(k.Empty());

	CHECK_THROWS(DynamicArray().Pop_back());
	CHECK_THROWS(DynamicArray(0, 2).Pop_back());
}

TEST_CASE("Clear Testing") {

	DynamicArray x(5, 10);
	x.Clear();
	CHECK(x.Size() == 0);
	CHECK(x.Empty());
	CHECK((x == DynamicArray()));
}

TEST_CASE("Erase Testing") {

	DynamicArray x{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int64_t s = x.Size();
	DynamicArray y{ 1, 2, 3, 5, 6, 7, 8, 9 };
	x.Erase(3);

	CHECK(x.Size() == s - 1);
	CHECK(x.Size() == y.Size());

	for (int64_t i = 0; i < y.Size(); i++) {
		CHECK(x[i] == y[i]);
	}

	DynamicArray q{ 2, 3, 5, 6, 7, 8, 9 };
	x.Erase(0);

	CHECK(x.Size() == s - 2);
	CHECK(x.Size() == q.Size());

	for (int64_t i = 0; i < q.Size(); i++) {
		CHECK(x[i] == q[i]);
	}

	DynamicArray g{ 2, 3, 5, 6, 7, 8 };
	x.Erase(x.Size() - 1);

	CHECK(x.Size() == s - 3);
	CHECK(x.Size() == g.Size());

	for (int64_t i = 0; i < g.Size(); i++) {
		CHECK(x[i] == g[i]);
	}

	CHECK_THROWS(DynamicArray(10, 1).Erase(12));
	CHECK_THROWS(DynamicArray(10, 1).Erase(-12));
	CHECK_THROWS(DynamicArray().Erase(1));
	CHECK_THROWS(DynamicArray(0, 5).Erase(3));
	CHECK_THROWS(DynamicArray({}).Erase(-1));
}

TEST_CASE("Resize Testing") {

	DynamicArray x(6, 1);
	DynamicArray t(x);
	int64_t s = x.Size();
	
	x.Resize(10);
	CHECK(x.Size() == 10);
	CHECK(s < 10);
	for (int64_t i = 0; i < s; i++) {
		CHECK(x[i] == t[i]);
	}
	for (int64_t i = s; i < x.Size(); i++) {
		CHECK(x[i] == 0);
	}

	x.Resize(3);
	CHECK(x.Size() == 3);
	CHECK(s > 3);
	for (int64_t i = 0; i < x.Size(); i++) {
		CHECK(x[i] == t[i]);
	}

	x.Resize(0);
	CHECK(x.Size() == 0);
	CHECK(s > 0);
	CHECK(x.Empty());

	CHECK_THROWS(DynamicArray().Resize(-20));
	CHECK_THROWS(DynamicArray(1).Resize(-1));
	CHECK_THROWS(DynamicArray(1, 2).Resize(-2));
	CHECK_THROWS(DynamicArray({ 1,2,3 }).Resize(-3));
}

TEST_CASE("Assign Testing") {

	DynamicArray x(5, 2);

	x.Assign(10, 3);
	CHECK(x.Size() == 10);
	for (int64_t i = 0; i < x.Size(); i++) {
		CHECK(x[i] == 3);
	}
	
	x.Assign(0, 3);
	CHECK(x.Size() == 0);
	CHECK(x.Empty());

	CHECK_THROWS(DynamicArray(2).Assign(-10, 3));
	CHECK_THROWS(DynamicArray(2, 2).Assign(-1, 3));
	CHECK_THROWS(DynamicArray(0).Assign(-2, 3));
	CHECK_THROWS(DynamicArray({ 1,2,3 }).Assign(-3, 3));
}

TEST_CASE("Begin End Testing") {

	DynamicArray x(3, 4);
	CHECK(*(x.begin()) == x[0]);

	DynamicArray y(0);
	CHECK(*(y.begin()) == *(y.end()));
}

TEST_CASE("Swap Testing") {

	DynamicArray x = { 0, 2, 4 };
	DynamicArray x1(x);
	DynamicArray y = { 1, 3, 5, 7, 9, 11 };
	DynamicArray y1(y);

	x.Swap(y);
	CHECK(x.Size() == y1.Size());
	CHECK(y.Size() == x1.Size());
	CHECK(x.Capacity() == y1.Capacity());
	CHECK(y.Capacity() == x1.Capacity());
	CHECK((x == y1));
	CHECK((x1 == y));
	
	DynamicArray k;
	x.Swap(k);
	CHECK(x.Empty());
}

TEST_CASE("Operator == Testing") {

	DynamicArray x = { 9, 8, 7, 6, 5, 4, 3, 2 ,1 };
	DynamicArray y = { 9, 8, 7, 6, 5, 4, 3, 2 ,1 };

	CHECK((x == y));
	CHECK(x.Size() == y.Size());
	for (int64_t i = 0; i < x.Size(); i++) {
		CHECK(x[i] == y[i]);
	}

	DynamicArray p = { 1, 2, 3 };
	DynamicArray q = { 1, 2 };
	CHECK((p == q) == false);

	DynamicArray s = { 1, 2, 3 };
	DynamicArray c = { 3, 2, 1 };
	CHECK((s == c) == false);

	DynamicArray w(3, 6);
	DynamicArray v(3, 6);
	w.Push_back(1); //чтобы изменить capacity
	w.Pop_back();

	CHECK(w.Capacity() != v.Capacity());
	CHECK((w == v));
	CHECK(w.Size() == v.Size());
	for (int64_t i = 0; i < w.Size(); i++) {
		CHECK(w[i] == v[i]);
	}
}

TEST_CASE("Operator != Testing") {

	DynamicArray x = { 9, 8, 7, 6 };
	DynamicArray y = { 9, 6, 6, 6 };
	CHECK((x != y));

	DynamicArray m(1, 2);
	DynamicArray n(2, 2);
	CHECK((m != n));

	DynamicArray p = { 1, 2, 3 };
	DynamicArray q = { 1, 2, 3 };
	CHECK((p != q) == false);
	CHECK((p == q) == true);
	CHECK(p.Capacity() == q.Capacity());
}

TEST_CASE("Insert Testing") {

	DynamicArray x = { 1, 2, 3 };
	int64_t s = x.Size();
	DynamicArray y = { 0, 1, 2, 3 };
	DynamicArray z = { 0, 1, 2, 3, 4 };
	DynamicArray q = { 0, 1, 2, 55, 3, 4 };
	
	x.Insert(0, 0);
	CHECK((x == y));
	CHECK(x[0] == 0);
	CHECK(x.Size() == s + 1);

	x.Insert(4, 4);
	CHECK((x == z));
	CHECK(x[4] == 4);
	CHECK(x.Size() == s + 2);

	x.Insert(3, 55);
	CHECK((x == q));
	CHECK(x[3] == 55);
	CHECK(x.Size() == s + 3);

	CHECK_THROWS(x.Insert(-1, 2));
	CHECK_THROWS(x.Insert(x.Size() + 10, 2));
}

TEST_CASE("Operator = Testing") {

	DynamicArray x(3, 3);
	DynamicArray y(5, 5);

	x = y;
	CHECK(x.Size() == y.Size());
	CHECK((x == y));

	x = DynamicArray();
	CHECK(x.Empty());
	CHECK(x.Size() == 0);
}

