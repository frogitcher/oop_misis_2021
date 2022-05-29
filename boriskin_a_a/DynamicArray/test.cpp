#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic_array.h"

TEST_CASE("Testing the constructors")
{
	DynamicArray a;
	CHECK(a.Size() == 0);
	CHECK(a.Capacity() == 0);
	CHECK(a.Empty() == true);

	DynamicArray b(4, 18);
	CHECK(b.Size() == 4);
	CHECK(b.Capacity() == 4);
	for (int i=0; i<b.Size(); ++i)
	{
		CHECK(b[i] == 18);
	}
	
	DynamicArray c(b);
	CHECK(c.Size() == 4);
	CHECK(c.Capacity() == 4);
	for (int i = 0; i < c.Size(); ++i)
	{
		CHECK(c[i] == 18);
	}

	DynamicArray d({1, 2, 3, 4, 5});
	CHECK(d.Size() == 5);
	CHECK(d.Capacity() == 5);
	for (int i=0; i<d.Size(); ++i)
	{
		CHECK(d[i] == i+1);
	}
}

TEST_CASE("Testing the operators")
{
	DynamicArray array_1({1, 2, 3, 4, 5});
	DynamicArray array_2;
	DynamicArray array_3({10, 20, 30, 40, 50});
	array_2 = array_1;
	CHECK(array_1 == array_2);
	for (int i=0; i<array_1.Size(); ++i)
	{
		CHECK(array_1[i] == array_2[i]);
		CHECK(array_1[i] == i+1);
		CHECK(array_1[i] != array_3[i]);
	}
}

TEST_CASE("Testing the methods")
{
	//resize()
	DynamicArray x({1, 2, 3, 4, 5});
	CHECK(*(x.begin()) == 1);
	CHECK(*(x.end()-1) == 5);
	CHECK(!(x.Empty()));
	CHECK(x.Size() == 5);
	CHECK(x.Capacity() == 5);
	x.push_back(6);
	CHECK(x.At(5) == 6);
	x.pop_back();
	CHECK(x.Size() == 5);
	x.erase(3);
	CHECK(x[3] == 5);
	x.insert(2, 3);
	CHECK(x[3] == 3);
	x.clear();
	CHECK(x.Size() == 0);

	DynamicArray a({1, 2, 3, 4, 5});
	DynamicArray b({10, 20, 30, 40, 50});
	a.swap(b);
	for (int i=0; i<a.Size(); ++i)
	{
		CHECK(b[i] == i+1);
		CHECK(a[i] == (i+1)*10);
	}
	a.resize(2);
	CHECK(a.Size() == 2);
}


TEST_CASE("Testing the throws")
{
	DynamicArray a; 
	CHECK_THROWS_WITH(a.pop_back(), "you can not delete element because size is too small");
	DynamicArray b({1, 2, 3});
	CHECK_THROWS_WITH(b.At(4), "your size is bigger than size of array");
}
