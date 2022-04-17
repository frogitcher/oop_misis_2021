#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "DynArr.h"
#include "doctest.h"

#include <string>

TEST_CASE("Testing init functions") {
	DynArr<int> arr1;
	DynArr<int> arr2(3); // { 0, 0, 0 }
	DynArr<int> arr3(2, 2); // { 2, 2 }
	DynArr<std::string> arr5{"a", "b"};
	DynArr<std::string> arr6(arr5); // { "" , "" }
	CHECK(arr1.Empty());
	CHECK(arr2 == DynArr<int>{0, 0, 0});
	CHECK(arr3 == DynArr<int>{2, 2});
	CHECK(arr5 == DynArr<std::string>{"a", "b"});
	CHECK(arr6 == DynArr<std::string>{"a", "b"});
}

TEST_CASE("Testing main functionality of DynArr") {
	DynArr<double> arr1{ 0.5f, 0.2f, 1.5f };
	DynArr<double> arr2(3); // { 0.f, 0.f, 0.f }
	DynArr<double> arr3(2, 1.34f); // { 1.34f, 1.34f }
	DynArr<double> arr4{};
	CHECK(!arr2.Empty());
	CHECK(arr2.Size() == 3);
	CHECK(*(arr2.Data()) == 0.f);
	CHECK(arr2.Data() == arr2.Begin());
	CHECK(arr3.Back() == arr3.Front());
	CHECK(arr1.Back() == 1.5f);
	CHECK(arr1.Front() == 0.5f);
	arr2.Swap(arr3);
	CHECK(arr3 == DynArr<double>{0.f, 0.f, 0.f});
	CHECK(*(arr2.End() - 1) == 1.34f);
	CHECK_THROWS_WITH(arr4.Back(), "Cannot get last element of an empty array");
	CHECK_THROWS_WITH(arr4.Front(), "Cannot get first element of an empty array");
	arr1.SwapItemsAt(0, 2);
	CHECK(arr1 == DynArr<double>{ 1.5f, 0.2f, 0.5f });
	CHECK(arr1.At(1) == 0.2f);
	CHECK_THROWS_WITH(arr4.At(3), "Index is out of range");
}

TEST_CASE("Testing push/pop methods") {
	DynArr<int> arr1{ 1, 0, -1 };
	DynArr<int> arr2{ 0, 7 };
	DynArr<int> arr3{ 5, 1 };
	DynArr<double> arr4;
	arr1.Pop_back();
	CHECK(arr1 == DynArr<int>{ 1, 0 });
	arr1.Pop_front();
	CHECK(arr1 == DynArr<int>{ 0 });
	arr1.Push_back(-2);
	CHECK(arr1.Back() == -2);
	arr1.Push_back(arr2);
	CHECK(arr1 == DynArr<int>{ 0, -2, 0, 7 });
	arr2.Push_front(-8);
	CHECK(arr2 == DynArr<int>{ -8, 0, 7 });
	arr2.Push_front(arr3);
	CHECK(arr2 == DynArr<int>{ 5, 1, -8, 0, 7});
	arr2.Clear();
	CHECK(arr2.Empty());
	CHECK_THROWS_WITH(arr4.Pop_back(), "Cannot pop last element from an empty array");
	CHECK_THROWS_WITH(arr4.Pop_front(), "Cannot pop first element from an empty array");
}

TEST_CASE("Testing insert & erase methods") {
	DynArr<char> arr1{ '0', '1', '2' };
	DynArr<char> arr2{ '0', '2' };
	arr2.Insert(1, '1');
	CHECK(arr1 == arr2);
	arr1.Erase(1, 2);
	CHECK(arr1.Back() == '0');
	arr1.Insert(0, '0');
	CHECK(arr1 == DynArr<char>{'0', '0'});
	arr1.EraseIf('0');
	CHECK(arr1.Empty());
	CHECK_THROWS_WITH(arr2.Insert(4, '4'), "Cannot perform insertion - provided index is out of range");
	CHECK_THROWS_WITH(arr2.Erase(1, 5), "Last array index is lower than last provided index to erase");
	CHECK_THROWS_WITH(arr2.Erase(1, -1), "Cannot erase negative amount of items");
}

TEST_CASE("Testing assign & resize methods") {
	DynArr<int> arr1;
	arr1.Assign(5, 4);
	CHECK(arr1.Size() == 5);
	CHECK(arr1.Back() == 4);
	CHECK(arr1.Front() == 4);
	arr1.Resize(6);
	CHECK(arr1.Size() == 6);
	CHECK(arr1.Back() == 0);
	CHECK(arr1.Front() == 4);
	arr1.Resize(8, 3);
	CHECK(arr1.Size() == 8);
	CHECK(arr1.Back() == 3);
	CHECK(arr1.Front() == 4);
	arr1.Resize(2);
	CHECK(arr1.Size() == 2);
	CHECK(arr1.Back() == 4);
	CHECK(arr1.Front() == 4);
}

TEST_CASE("Testing additional DynArr functionality") {
	DynArr<int> arr1{1, 2, 3, 3};
	CHECK(arr1.SubArr(0, 1) == DynArr<int>{ 1, 2 });
	CHECK_THROWS_WITH(arr1.SubArr(2, 1), "Last indext of sub-array cannot be less than first");
	CHECK_THROWS_WITH(arr1.SubArr(2, 10), "Given sub-array borders are out of parent array range");
	arr1.ReplaceAll(3, 0);
	CHECK(arr1 == DynArr<int>{ 1, 2, 0, 0 });
	arr1.Reverse();
	CHECK(arr1 == DynArr<int>{ 0, 0, 2, 1 });
	CHECK(arr1.Contains(1));
	CHECK(!arr1.Contains(3));
	CHECK(arr1.Count(0) == 2);
	CHECK(arr1.Count(-1) == 0);
}

TEST_CASE("Testing non-comparasment operators") {
	DynArr<float> arr1{ 0.1f, 0.2f };
	DynArr<float> arr2;
	arr2 = arr1;
	CHECK(arr2 == arr1);
	arr2 += arr1;
	CHECK(arr2 == DynArr<float>{ 0.1f, 0.2f, 0.1f, 0.2f });
	CHECK(arr1 + arr1 == arr2);
	CHECK(arr1[0] == 0.1f);
	CHECK(arr2[2] == 0.1f);
}

TEST_CASE("Testing comparasment operators") {
	DynArr<std::string> arr1{ "abc", "ab" };
	DynArr<std::string> arr2{ "abc", "a" };
	DynArr<std::string> arr3{ "abc", "a", "dca"};
	CHECK(arr1 != arr2);
	CHECK(arr1 > arr2);
	CHECK(arr2 < arr3);
	CHECK(arr3 >= arr2);
	CHECK(arr2 <= arr1);
	CHECK(arr2 >= arr2);
	CHECK(arr3 == arr3);
}