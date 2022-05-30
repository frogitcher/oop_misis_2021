#pragma once
#include <initializer_list>
#include <stddef.h>
#include <stdexcept>
class DynamicArray {
public:
	//Dynamic_Array() = default;
	DynamicArray(size_t length = 0, int value = 0);
	DynamicArray(const DynamicArray& other);
	DynamicArray(const std::initializer_list<int>& list);
	~DynamicArray();
	inline const size_t Size() const {
		return size;
	};
	inline const size_t Capacity() const {
		return capacity;
	};
	inline int* Data() const {
		return data;
	};
	inline bool Empty() const {
		return size == 0;
	};
	void push_back(int value);
	inline void pop_back() {
		if (size == 0) {
			throw std::out_of_range("Array Size <0");
		}
		else {
			this->size--;
		};
	};
	inline void clear() {
		size = 0;
	};
	void erase(size_t index);
	void insert(size_t index, int num);
	void assign(size_t new_size, int value);
	void swap(DynamicArray& other);
	inline int* begin() const {
		return data;
	};
	inline int* end() const {
		return data + Size();
	};
	bool operator==(const DynamicArray& other) const;
	bool operator>=(const DynamicArray& other) const;
	bool operator>(const DynamicArray& other) const;
	bool operator<(const DynamicArray& other) const;
	bool operator<=(const DynamicArray& other) const;
	bool operator!=(const DynamicArray& other) const;
	DynamicArray& operator=(const DynamicArray other);
	inline int& operator[](size_t i) const { return *(data + i); };
	int& at(size_t i) const;

private:
	size_t size = 0;
	size_t capacity = 0;
	int* data;
	void reallocate(size_t new_capacity);
};