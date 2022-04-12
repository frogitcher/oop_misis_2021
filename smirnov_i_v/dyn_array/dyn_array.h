#pragma once
#include <cstdint>
#include <initializer_list>

class DynArray
{
public:
	DynArray(int64_t length = 0, int value = 0);
	DynArray(const DynArray& other);
	DynArray(const std::initializer_list<int>& list);
	~DynArray();

	int64_t Size() const;
	int64_t Capacity() const;
	bool Empty() const;
	int& operator[](int64_t i) const;
	int& at(int64_t i) const;

	void push_back(int value);
	void pop_back();
	void clear();
	void erase(int64_t i);
	void resize(int64_t new_size);
	void assign(int64_t new_size, int value);
	void insert(int64_t i, int value);
	inline int* begin() const;
	inline int* end() const;
	void swap(DynArray& other);

	bool operator==(const DynArray& other) const;
	bool operator!=(const DynArray& other) const;
	DynArray& operator=(const DynArray& other);
private:
	int64_t capacity = 0;
	int64_t size = 0;
	int* data;
	void reallocate(int64_t new_capacity);
};

