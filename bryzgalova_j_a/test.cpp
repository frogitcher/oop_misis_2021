#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic_array.h"

TEST_CASE("Testing dynamic_array") {
    DynamicArray a;
	CHECK(a.begin() == a.GetData());
    CHECK(a.Size() == 0);

    DynamicArray b(7, 4);
    CHECK(b.Size() == 7);
    CHECK(b.Capacity() >= b.Size());

    DynamicArray c(b);
    CHECK(c.Size() == b.Size());
    CHECK(c.Capacity() == b.Capacity());
    for (int64_t i = 0; i < b.Size(); i++) {
        CHECK(&(c[i]) == (c.begin() + i));
        CHECK(c[i] == b[i]);
    }

    DynamicArray d({1, 2, 3, 4, 5, 6, 7});
    CHECK_FALSE(c == d);
    CHECK(c != d);
    CHECK_FALSE(c != b);
	
	

    CHECK_THROWS_WITH(a.at(1), "Index is out");

    int64_t old_size = b.Size();
    b.push_back(7);
    CHECK(b.Size() == old_size + 1);
    CHECK(b[b.Size() - 1] == 7);

    DynamicArray d_copy(d);
    d.reallocate(d, 30);
    CHECK(d_copy.Size() == d.Size());
    CHECK(d.Capacity() == d_copy.Capacity());
    for (int64_t i = 0; i < d.Size(); ++i) {
        CHECK(d[i] == d_copy[i]);
    }
	
	CHECK(a.Empty());
    CHECK_FALSE(b.Empty()); 

    old_size = d.Size();
    d.pop_back();
    CHECK(d.Size() == old_size - 1);
    for (int64_t i = 0; i < d.Size(); ++i) {
        CHECK(d[i] == d_copy[i]);
    }
    CHECK_THROWS_WITH(a.pop_back(), "Array is empty"); 

    d.clear();
    CHECK(d.Empty());

    
    DynamicArray b_copy(b); // b = {4,4,4,4,4,4,4,7}
    b.erase(0);
    CHECK(b.Size() == b_copy.Size() - 1);
    for (int64_t i = 0; i < b.Size(); ++i) {
        CHECK(b[i] == b_copy[i + 1]);
    }
    b.erase(3);
    CHECK(b.Size() == b_copy.Size() - 2);
    for (int64_t i = 0; i < b.Size(); ++i) {
        if (i >= 3) {
            CHECK(b[i] == b_copy[i + 2]);
            continue;
        }
        CHECK(b[i] == b_copy[i + 1]);
    }
    b.erase(b.Size() - 1);
    CHECK(b.Size() == b_copy.Size() - 3);
    for (int64_t i = 0; i < b.Size(); ++i) {
        if (i >= 3) {
            CHECK(b[i] == b_copy[i + 2]);
            continue;
        }
        CHECK(b[i] == b_copy[i + 1]);
    }

    
    old_size = b.Size();//b = {4,4,4,4,4}
    b.resize(13, 15);
    CHECK(b.Size() == 13);
    for (int64_t i = 0; i < old_size; ++i) {
        CHECK(b[i] == 4);
    }
    for (int64_t i = old_size + 1; i < b.Size(); ++i) {
        CHECK(b[i] == 15);
    }

    CHECK_THROWS_WITH(b.resize(-17, 18), "Length < 0");

    b.resize(0);
    CHECK(b.Empty());

    b.assign(4, 5);
    CHECK(b.Size() == 4);
    for (int64_t i = 0; i < b.Size(); ++i) {
        CHECK(b[i] == 5);
    }

    CHECK_THROWS_WITH(b.assign(-17, 18), "Length < 0");

    b.assign(0);
    CHECK(b.Empty());
    CHECK(b.end() == b.GetData() + 0);

    int64_t old_size_c = c.Size();
    int64_t old_size_d = d.Size();
    int64_t old_capacity_c = c.Capacity();
    int64_t old_capacity_d = d.Capacity();
	int* old_data_d = d.GetData();
    int* old_data_c = c.GetData();
    
	d.swap(c);
    CHECK(d.Size() == old_size_c);
    CHECK(c.Size() == old_size_d);
    CHECK(d.Capacity() == old_capacity_c);
    CHECK(c.Capacity() == old_capacity_d);
    CHECK(d.GetData() == old_data_c);
    CHECK(c.GetData() == old_data_d);

    d_copy = d;
    d.insert(0, 79);
    CHECK(d[0] == 79);
    for (int64_t i = 1; i < d.Size(); ++i) {
        CHECK(d[i] == d_copy[i - 1]);
    }
    d_copy = d;
    d.insert(14, 31);
    CHECK(d[14] == 31);
    for (int64_t i = 0; i < d.Size(); ++i) {
        if (i == 14) {
            continue;
        }
        if (i > 14) {
            CHECK(d[i] == d_copy[i - 1]);
            continue;
        }
        CHECK(d[i] == d_copy[i]);
    }
    
	
	d_copy = d;
    d.insert(17, 0);
    CHECK(d[17] == 0);
    for (int64_t i = 0; i < d.Size(); ++i) {
        if (i == 17) {
            continue;
        }
        CHECK(d[i] == d_copy[i]);
    }
}