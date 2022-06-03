#pragma once
#include <cmath>
#include <cstdint>
#include <initializer_list>
#include <algorithm>

class Set
{
public:
	Set(const size_t size, int value);
	~Set();
	inline bool Empty() const {
		return size == 0;
	}
	inline int* GetData() const {
		return data;
	}
	int64_t Size() const;
	void Insert(int value); // Добавлять только тогда, когда элемента нет в массиве
	int Find(int value);
	void Erase(int64_t index);
	inline int* Begin() const {
		return data;
	}

	inline int* End() const {
		return data + size;
	}
	Set& operator=(const Set& rhs);
	int& operator[](int index);


private:
	int* data = nullptr;
	int size = 0;
};