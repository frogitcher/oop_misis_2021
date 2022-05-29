#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dyn_array.h"

TEST_CASE("Testing dynamic array") {
	DynArray a;
	CHECK(a.Size() == 0);
	CHECK(a.Capacity() == 0);
	CHECK(a.begin() != nullptr);
	CHECK(a.Empty());

	DynArray d(8, 3);
	CHECK(d.Size() == 8);
	CHECK(d.Capacity() >= d.Size());
	for (auto& it : d) {
		CHECK(it == 3);
	}


	DynArray sample({3, 7, 8, 11, -4 });
	CHECK(sample.Size() == 5);
	CHECK(sample.Capacity() >= sample.Size());
	CHECK(sample[0] == 3);
	CHECK(sample[1] == 7);
	CHECK(sample[2] == 8);
	CHECK(sample[3] == 11);
	CHECK(sample[4] == -4);

	DynArray c(sample);
	CHECK(c.Size() == sample.Size());
	CHECK(c.Capacity() >= sample.Size());
	for (int i = 0; i < c.Size(); i++) {
		CHECK(c[i] == sample[i]);
	}

	c[2] = 15;
	CHECK(c[2] == 15);
	CHECK(c[2] == *(c.begin()+2));
	
	c.at(3) = 20;
	CHECK(c[3] == 20);
	CHECK(&c.at(3) == &c[3]);
	CHECK_THROWS_WITH(c.at(5), "Index out of array's range");

	c = sample;
	int64_t old_size(c.Size());
	c.push_back(2);
	CHECK(c.Size() == old_size + 1);
	CHECK(c[5] == 2);
	for (int i = 0; i < sample.Size(); i++) {
		CHECK(c[i] == sample[i]);
	}

	old_size = c.Size();
	c.pop_back();
	CHECK(c.Size() == old_size - 1);
	for (int i = 0; i < c.Size(); i++) {
		CHECK(c[i] == sample[i]);
	}
	DynArray e;
	CHECK_THROWS_WITH(e.pop_back(), "Array is already empty");
	
	c.clear();
	CHECK(c.Size() == 0);

	c = sample; // c = {3, 7, 8, 11, -4}
	c.erase(0);
	CHECK(c.Size() == sample.Size()-1);
	for (int i = 0; i < c.Size(); i++) {
		CHECK(c[i] == sample[i + 1]);
	}
	c = sample; // reset
	c.erase(c.Size() - 1);
	CHECK(c.Size() == sample.Size() - 1);
	for (int i = 0; i < c.Size(); i++) {
		CHECK(c[i] == sample[i]);
	}
	c = sample;
	c.erase(2);
	CHECK(c.Size() == sample.Size() - 1);
	for (int i = 0; i < c.Size(); i++) {
		if (i <= 1) {
			CHECK(c[i] == sample[i]);
		}
		else {
			CHECK(c[i] == sample[i + 1]);
		}
	}

	c.resize(0);
	CHECK(c.Size() == 0);
	c.resize(20);
	CHECK(c.Size() == 20);
	CHECK_THROWS_WITH(c.resize(-5), "Size can't be negative");

	c.assign(5, 4);
	CHECK(c.Size() == 5);
	for (int i = 0; i < c.Size(); i++) {
		CHECK(c[i] == 4);
	}
	CHECK_THROWS_WITH(c.assign(-5, 4), "Size can't be negative");
	c.assign(0, 5);
	CHECK(c.Size() == 0);

	c = sample;
	c.insert(3, 15);
	CHECK(c.Size() == sample.Size() + 1);
	CHECK(c[3] == 15);
	for (int i = 0; i < sample.Size(); i++) {
		if (i <= 2) {
			CHECK(c[i] == sample[i]);
		}
		else {
			CHECK(c[i + 1] == sample[i]);
		}
	}


	CHECK(c.begin() == c.end() - c.Size());
	c.clear();
	CHECK(c.begin() == c.end());
	
	
	c = sample;
	//d = {3, 3, 3, 3, 3, 3, 3, 3} c = {3, 7, 8, 11, -4}
	int64_t old_size_c = c.Size();
	int64_t old_size_d = d.Size();
	int64_t old_capacity_c = c.Capacity();
	int64_t old_capacity_d = d.Capacity();
	int* old_data_c = c.begin();
	int* old_data_d = d.begin();
	c.swap(d);
	CHECK(c.Size() == old_size_d);
	CHECK(d.Size() == old_size_c);
	CHECK(c.Capacity() == old_capacity_d);
	CHECK(d.Capacity() == old_capacity_c);
	CHECK(c.begin() == old_data_d);
	CHECK(d.begin() == old_data_c);

	d = c;
	CHECK(c == d);
	d.insert(2, 3);
	CHECK(c != d);
}