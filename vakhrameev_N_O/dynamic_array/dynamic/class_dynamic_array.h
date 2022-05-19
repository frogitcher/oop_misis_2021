#pragma once
#include <initializer_list>
#include <stddef.h>
#include <string>
class Dynamic_array
{
public:
	Dynamic_array(size_t n=0, int value=0);
	Dynamic_array(const Dynamic_array& other);
	Dynamic_array(const std::initializer_list<int>& other);
	~Dynamic_array();

	Dynamic_array& operator=(const Dynamic_array& other);
	size_t Capacity() const;
	size_t Size() const;
	bool Empty() const;
	int& operator[](size_t i);
	void push_back(int value);
	void pop_back();
	void clear();
	void assign(size_t n, int value=0);
	void erase(size_t index);
	int* begin() const;
	int* end() const;
	void swap(Dynamic_array& other);
	bool operator==(const Dynamic_array& other)const;
	bool operator!=(const Dynamic_array& other)const;
	bool operator>=(const Dynamic_array& other)const;
	bool operator<=(const Dynamic_array& other)const;
	bool operator>(const Dynamic_array& other)const;
	bool operator<(const Dynamic_array& other)const;

private:
	size_t size = 0;
	size_t capacity = 0;
	int* data;
};
