#pragma once
#include <iostream>
class dinmas {
private:
	size_t capacity = 0;
	int* data;
	size_t size;
public:
	dinmas();
	dinmas(size_t lenght, int value = 0);
	dinmas(const dinmas& other);
	dinmas(const std::initializer_list<int>& list);
	~dinmas();
	size_t Size() const;
	size_t Capacity() const;
	bool Empty() const;
	int& operator[](size_t i) const;
	int& at(size_t i) const;
	void push_back(int value);
	void Clear();
	void Erase(size_t index);
	void Resize(size_t newsize);
	void assign(size_t new_size, int value);
	int* begin() const;
	int* end() const;
	void swap(dinmas& other);
	void pop_back();
	void insert(const int index, const int value);
	bool operator== (const dinmas& other) const;
	bool operator!= (const dinmas& other) const;
	void operator= (const dinmas& other);
};
