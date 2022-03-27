#pragma once
#include <initializer_list>
#include <stddef.h>
class Dynamic_Array {
public:
	Dynamic_Array() = default;
	Dynamic_Array(size_t length, int value=0);
	Dynamic_Array(const Dynamic_Array& other);
	//Dynamic_Array(const std::initializer_list<int>& list);
	~Dynamic_Array();
	const size_t Size() const;
	const size_t Capacity() const;
	int* Data() const;
	bool Empty() const;
	void push_back(int value);
	void pop_back();
	void clear();
	void erase(size_t index);
	void insert(size_t index, int num);
	void assign(size_t new_size, int value);
	void swap(Dynamic_Array& other);
	int* begin();
	int* end();
	bool operator==(const Dynamic_Array& other) const;
	bool operator>=(const Dynamic_Array& other) const;
	bool operator>(const Dynamic_Array& other) const;
	bool operator<(const Dynamic_Array& other) const;
	bool operator<=(const Dynamic_Array& other) const;
	bool operator!=(const Dynamic_Array& other) const;
	Dynamic_Array& operator=(Dynamic_Array other);
	int& operator[](size_t i) const;

private:
	size_t size = 0;
	size_t capacity = 0;
	int* data;

};