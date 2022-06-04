#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dyn_array.h"
#include <string>
#include <vector>
#include <iostream>

TEST_CASE ("zzz") {
	CHECK (Dyn_array<int>(5, -2)[2] == -2);
	CHECK (Dyn_array<std::string>(5, "fst")[2] == "fst");
	CHECK (Dyn_array<std::string>(5, "fst")[2][2] == 't');
	CHECK (Dyn_array<std::vector<int> >(5, std::vector<int> (3, 11))[2] == std::vector<int> (3, 11));
	CHECK (Dyn_array<std::vector<int> >(5, std::vector<int> (3, 11))[2][0] == 11);

	CHECK (Dyn_array<int>(5, -2)[2] == Dyn_array<int>(5, -2)[2]);
	CHECK (Dyn_array<int>(5, -2)[2] == Dyn_array<int>(5, -2)[1]);

	Dyn_array<std::vector<int> > a(5, std::vector<int> (3, 11));
	CHECK (Dyn_array<std::vector<int> >(a)[0] == a[0]);

	Dyn_array<int > b(5,11);
	it<int> x = b.begin();
	CHECK(*x == 11);
	b.resize(1000, 123);
	CHECK(*x == 11);
	CHECK(*b.begin() == 11);
	b.insert(1000, -1);
	CHECK(b[1000] == -1);
	CHECK_THROWS_WITH(b.insert(1002, 10), "Out of range");
}
TEST_CASE ("reisze, size") {
	SUBCASE("") {
		Dyn_array<std::vector<int> > a(5, std::vector<int> (3, 11));
		CHECK (a.size() == 5);
	}
	SUBCASE("") {
		Dyn_array<std::vector<int> > a(5, std::vector<int> (3, 11));
		a.resize(3);
		CHECK (a.size() == 3);
	}
	SUBCASE("") {
		Dyn_array<std::vector<int> > a(5, std::vector<int> (3, 11));
		a.resize(10);
		CHECK (a.size() == 10);
	}
	SUBCASE("") {
		Dyn_array<std::vector<int> > a(5, std::vector<int> (3, 11));
		a.resize(3, std::vector<int>(2, -1));
		CHECK (a[1] == std::vector<int>(3, 11));
	}
	SUBCASE("") {
		Dyn_array<std::vector<int> > a(5, std::vector<int> (3, 11));
		a.resize(10, std::vector<int>(2, -1));
		CHECK (a[9] == std::vector<int>(2, -1));
	}
}
TEST_CASE ("==") {
	CHECK(Dyn_array<std::vector<int> >(5, std::vector<int> (3, 11)) == Dyn_array<std::vector<int> >(5, std::vector<int> (3, 11)));
}
TEST_CASE ("push_back, pop_back") {
	SUBCASE ("") {
		Dyn_array<std::vector<int> > a(5, std::vector<int> (3, 11));
		a.push_back(std::vector<int>(2, -1));
		CHECK(a.size() == 6);
		CHECK(a[a.size() - 2] == std::vector<int>(3, 11));
		CHECK(a[a.size() - 1] == std::vector<int>(2, -1));
		Dyn_array<std::vector<int> > b;
		b.push_back(std::vector<int>(3, 11));
		b.push_back(std::vector<int>(3, 11));
		b.push_back(std::vector<int>(3, 11));
		b.push_back(std::vector<int>(3, 11));
		b.push_back(std::vector<int>(3, 11));
		b.push_back(std::vector<int>(2, -1));
		CHECK(b == a);
	}
	
	
}


TEST_CASE("Testing dynamic array") {
	Dyn_array<int> a;
	CHECK(a.size() == 0);
	CHECK(a.capacity() == 1);
	//CHECK(a.begin() != nullptr);
	CHECK(a.empty());

	Dyn_array<int> d(8, 3);
	CHECK(d.size() == 8);
	CHECK(d.capacity() >= d.size());


	Dyn_array<int> sample({3, 7, 8, 11, -4 });
	CHECK(sample.size() == 5);
	CHECK(sample.capacity() >= sample.size());
	CHECK(sample[0] == 3);
	CHECK(sample[1] == 7);
	CHECK(sample[2] == 8);
	CHECK(sample[3] == 11);
	CHECK(sample[4] == -4);

	Dyn_array<int> c(sample);
	CHECK(c.size() == sample.size());
	CHECK(c.capacity() >= sample.size());
	for (int i = 0; i < c.size(); i++) {
		CHECK(c[i] == sample[i]);
	}

	c[2] = 15;
	CHECK(c[2] == 15);
	CHECK(c[2] == *(c.begin()+2));
	
	c.at(3) = 20;
	CHECK(c[3] == 20);
	CHECK(&c.at(3) == &c[3]);
	//CHECK_THROWS_WITH(c.at(5), "Index out of array's range");

	c = sample;
	size_t old_size(c.size());
	c.push_back(2);
	CHECK(c.size() == old_size + 1);
	CHECK(c[5] == 2);
	for (int i = 0; i < sample.size(); i++) {
		CHECK(c[i] == sample[i]);
	}

	old_size = c.size();
	c.pop_back();
	CHECK(c.size() == old_size - 1);
	for (int i = 0; i < c.size(); i++) {
		CHECK(c[i] == sample[i]);
	}
	Dyn_array<int> e;
	//CHECK_THROWS_WITH(e.pop_back(), "Array is already empty");

	c.clear();
	CHECK(c.size() == 0);

	c = sample; // c = {3, 7, 8, 11, -4}
	c.erase(0);
	CHECK(c.size() == sample.size()-1);
	for (int i = 0; i < c.size(); i++) {
		CHECK(c[i] == sample[i + 1]);
	}
	c = sample; // reset
	c.erase(c.size() - 1);
	CHECK(c.size() == sample.size() - 1);
	for (int i = 0; i < c.size(); i++) {
		CHECK(c[i] == sample[i]);
	}
	c = sample;
	c.erase(2);
	CHECK(c.size() == sample.size() - 1);
	for (int i = 0; i < c.size(); i++) {
		if (i <= 1) {
			CHECK(c[i] == sample[i]);
		}
		else {
			CHECK(c[i] == sample[i + 1]);
		}
	}

	c.resize(0);
	CHECK(c.size() == 0);
	c.resize(20);
	CHECK(c.size() == 20);
	//CHECK_THROWS_WITH(c.resize(-5), "size can't be negative");

	c.assign(5, 4);
	CHECK(c.size() == 5);
	for (int i = 0; i < c.size(); i++) {
		CHECK(c[i] == 4);
	}
	//CHECK_THROWS_WITH(c.assign(-5, 4), "size can't be negative");
	c.assign(0, 5);
	CHECK(c.size() == 0);



	CHECK(c.begin() == (c.end() - c.size()));
	c.clear();
	CHECK(c.begin() == c.end());
	
	
	c = sample;
	//d = {3, 3, 3, 3, 3, 3, 3, 3} c = {3, 7, 8, 11, -4}
	size_t old_size_c = c.size();
	size_t old_size_d = d.size();
	size_t old_capacity_c = c.capacity();
	size_t old_capacity_d = d.capacity();
	it<int> old_data_c = c.begin();
	it<int> old_data_d = d.begin();
	c.swap(d);
	CHECK(c.size() == old_size_d);
	CHECK(d.size() == old_size_c);
	CHECK(c.begin() == old_data_c);
	CHECK(d.begin() == old_data_d);

	d = c;
	CHECK(c == d);
	d.insert(2, 3);
	CHECK(c != d);
}