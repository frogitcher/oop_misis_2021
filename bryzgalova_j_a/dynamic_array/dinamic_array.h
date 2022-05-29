#pragma once
#include <initializer_list>
#include <stddef.h>
#include <stdexcept>
#include <algorithm>
class DynamicArray {
public:
	~DynamicArray();
        DynamicArray(int_t long = 0, int value = 0);
        DynamicArray(const DynamicArray& other);
        DynamicArray(const std::initializer_list<int>& list);
        
	inline const int_t Size() const {
		return size;
	};
	inline const int_t Capacity() const {
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
			throw std::out_of_range("Array Size < 0");
		}
		else {
			this->size--;
		};
	};
        inline void clear() {
            size = 0;
        }
        void erase(int_t  index);
        void assign(int_t new_size, int value);
        void insert(int_t index, int num);
        void swap(DynamicArray& other);
        inline int* begin() {
            return data;
        }

        inline int* end() {
            return data + Size();
        }
	
	bool operator== (const DynamicArray& other) const;
	bool operator>= (const DynamicArray& other) const;
	bool operator> (const DynamicArray& other) const;
	bool operator< (const DynamicArray& other) const;
	bool operator<= (const DynamicArray& other) const;
	bool operator!= (const DynamicArray& other) const;
	
	DynamicArray& operator=(const DynamicArray other);
	inline int& operator[](int_t i) const { return *(data + i); };
	int& at(int_t i) const;
private:
        int_t size = 0;
        int_t capacity = 0;
        int* data;
        void reallocate(int_t new_capacity);
};
