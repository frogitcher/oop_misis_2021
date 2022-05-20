#pragma once
#include <iostream>
#include <initializer_list>
#include <cstdint>
class Dynamic {
private:
	size_t capacity = 0;
	size_t size = 0;
	int* data;
public:
	Dynamic(size_t _size=0, int value = 0);
	Dynamic(const Dynamic& other);
	Dynamic(const std::initializer_list <int>& list);
	~Dynamic();

	size_t Size() const;
	size_t Capacity() const;

	bool Empty() const;
	int& operator[] (size_t i) const;
	int& at(size_t i) const;
	void push_back(int value);
	void pop_back();
	void clear();
	void erase(size_t index);
	void insert(size_t index, int value);
	void resize(size_t new_size);
	void assign(size_t new_size, int value);
	void swap(Dynamic& other);

	int* begin();
	int* end();

	bool operator ==(const Dynamic& other) const;
	bool operator !=(const Dynamic& other) const;
	bool operator <=(const Dynamic& other) const;
	bool operator >=(const Dynamic& other) const;
	bool operator <(const Dynamic& other) const;
	bool operator >(const Dynamic& other) const;

	Dynamic& operator=(const Dynamic& other);

};