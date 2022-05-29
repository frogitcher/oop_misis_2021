#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic_array.h"

TEST_CASE("TEST") {
	DynamicArray a(8, 3);
	CHECK(a.Size() == 8);
	CHECK(a.Capacity() >= a.Size());
	for (auto& it : a) {
		CHECK(it == 3);
	}

	DynamicArray b;
	CHECK(b.Size() == 0);
	CHECK(b.Capacity() == 0);
	CHECK(b.begin() != nullptr);
	CHECK(b.Empty());

	DynamicArray c({3, 7, 8, 11, -4 });
	CHECK(c.Size() == 5);
	CHECK(c.Capacity() >= c.Size());
	CHECK(c[0] == 3);
	CHECK(c[1] == 7);
	CHECK(c[2] == 8);
	CHECK(c[3] == 11);
	CHECK(c[4] == -4);

	DynamicArray d(c);
	CHECK(d.Size() == c.Size());
	CHECK(d.Capacity() >= c.Size());
	for (int i = 0; i < d.Size(); i++) {
		CHECK(d[i] == c[i]);
	}

	d[2] = 15;
	CHECK(d[2] == 15);
	CHECK(d[2] == *(d.begin()+2));
	
	d.at(3) = 20;
	CHECK(d[3] == 20);
	CHECK(&d.at(3) == &d[3]);
	CHECK_THROWS_WITH(d.at(5), "Index out of range");

	d = c;
	size_t old_size(d.Size());
	d.push_back(2);
	CHECK(d.Size() == old_size + 1);
	CHECK(d[5] == 2);
	for (int i = 0; i < c.Size(); i++) {
		CHECK(d[i] == c[i]);
	}

	old_size = d.Size();
	d.pop_back();
	CHECK(d.Size() == old_size - 1);
	for (int i = 0; i < d.Size(); i++) {
		CHECK(d[i] == c[i]);
	}
	DynamicArray e;
	CHECK_THROWS_WITH(e.pop_back(), "Array is empty");
	
	d.clear();
	CHECK(d.Size() == 0);

	d = c;
	d.erase(0);
	CHECK(d.Size() == c.Size()-1);
	for (int i = 0; i < d.Size(); i++) {
		CHECK(d[i] == c[i + 1]);
	}
	d = c;
	d.erase(d.Size() - 1);
	CHECK(d.Size() == c.Size() - 1);
	for (int i = 0; i < d.Size(); i++) {
		CHECK(d[i] == c[i]);
	}
	d = c;
	d.erase(2);
	CHECK(d.Size() == c.Size() - 1);
	for (int i = 0; i < d.Size(); i++) {
		if (i <= 1) {
			CHECK(d[i] == c[i]);
		}
		else {
			CHECK(d[i] == c[i + 1]);
		}
	}

	d.resize(0);
	CHECK(d.Size() == 0);
	d.resize(20);
	CHECK(d.Size() == 20);
	CHECK_THROWS_WITH(d.resize(-5), "bad array new length");

	d.assign(5, 4);
	CHECK(d.Size() == 5);
	for (int i = 0; i < d.Size(); i++) {
		CHECK(d[i] == 4);
	}



	CHECK(d.begin() == d.end() - d.Size());
	d.clear();
	CHECK(d.begin() == d.end());
	
	
	d = c;
	size_t old_size_c = d.Size();
	size_t old_size_d = a.Size();
	size_t old_capacity_c = d.Capacity();
	size_t old_capacity_d = a.Capacity();
	int* old_data_c = d.begin();
	int* old_data_d = a.begin();
	d.swap(a);
	CHECK(d.Size() == old_size_d);
	CHECK(a.Size() == old_size_c);
	CHECK(d.Capacity() == old_capacity_d);
	CHECK(a.Capacity() == old_capacity_c);
	CHECK(d.begin() == old_data_d);
	CHECK(a.begin() == old_data_c);

	a = d;
	CHECK(d == a);

}