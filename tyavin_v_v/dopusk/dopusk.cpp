#include "dopusk.h"
#include <stdexcept>

stack::stack(int64_t _size, int value)
        : size(_size), capacity(_size) {
    data = new int[size];
    std::fill(begin(), end(), value);
}

stack::stack(const stack &other)
        : size(other.size), capacity(other.capacity) {
    data = new int[capacity];
    std::copy(other.data, other.data + other.size, data);
}

stack::~stack() { delete[] data; }

void stack::Push(int val) {
    if (size == capacity) {
		if (capacity == 0) {
			capacity = 1;
		} else {
			capacity *= 2;
		}
        realloc(capacity);
    }
	size++;
    data[size] = value;
}

int stack::Get() {
	return *(data + size);
}

void stack::Pop() {
    if (size - start <= 0) throw std::length_error("Stack is empty!");
	start++;
    size--;
	data++;
}

void stack::realloc(int64_t new_cap) {
    int *new_data = new int[new_cap];
    std::copy(data, data + size, new_data);
    delete[] data;
    data = new_data;
    capacity = new_cap;
}

stack &stack::operator=(const stack &rhs) {
    if (rhs.size > capacity){
        reallocate(rhs.size);
    }
    size = rhs.size;
    std::copy(rhs.data, rhs.data + size, data);
    return *this;
}
