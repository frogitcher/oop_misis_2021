#pragma once
#include <cstdint>
#include <initializer_list>

class arrayd {
public:
	arrayd(int64_t _size = 0, int val = 0);
	arrayd(const arrayd& other);
	arrayd(const std::initializer_list<int>& list);
	~arrayd() { delete[] data; }
	arrayd& operator=(const arrayd& rhs);

	void resize(int64_t new_size);
	void push_back(int val);
	void pop_back();
	void assign(int64_t new_size, int val = 0);
	void swap(arrayd& other);
	void insert(int64_t i, int val);
	void erase(int64_t i);

	int& operator[](int64_t i) const;
	int& at(int64_t i) const { return (*this)[i]; }
	bool operator==(const arrayd& rhs) const;
	bool operator!=(const arrayd& rhs) const { return !operator==(rhs); }

	int64_t Cap() { return cap; }
	int64_t Size() { return size; }
	int64_t Empty() { return size == 0; }
	void clear() { size = 0; }
	int* begin() const { return data; }
	int* end() const { return data + size; }
	int back() const { return *(data + size - 1); }
	int front() const { return *(data); }
private:
	int64_t size{0};
	int64_t cap{0};
	int* data;
	void realloc(int64_t new_cap);
};

