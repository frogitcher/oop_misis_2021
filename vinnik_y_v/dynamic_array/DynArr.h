#pragma once

#include <initializer_list>

template<typename T>
class DynArr
{
public:
	DynArr(size_t len = 0, const T& value = 0);
	DynArr(const DynArr& oth);
	DynArr(const std::initializer_list<T>& init_list);
	~DynArr() = default;
	const size_t Capacity();
	const size_t Size();
	int* Data() const;
	void Push_back(const T& value);
	void Push_back(const DynArr<T>& oth);
	void Pop_back();
	void Push_front(const T& value);
	void Push_front(const DynArr<T>& oth);
	void Pop_front();
	bool Empty() const;
	void Erase(size_t idx, int amount = 1);
	void Insert(size_t idx, T& value, int amount = 1);
	void Clear();
	T& At(int idx) const;
	void Assign(size_t _size, T& value);
	void Swap(DynArr& other);
	void SwapItemsAt(size_t i, size_t j);
	int* Begin() const;
	int* End() const;
	T& Back() const;
	T& Front() const;
	DynArr<T> SubArr(size_t first_idx, size_t last_idx);
	void ReplaceAll(T& key, T& value);
	void EraseAll(T& key);
	void Reverse();
	bool Contains(const T& key) const;
	int Count(const T& key) const;

	DynArr<T>& operator=(const DynArr& other);
	inline T& operator[](size_t i) const;

	bool operator==(const DynArr& other) const;
	bool operator!=(const DynArr& other) const;
	bool operator>=(const DynArr& other) const;
	bool operator>(const DynArr& other) const;
	bool operator<(const DynArr& other) const;
	bool operator<=(const DynArr& other) const;

	bool operator==(std::initializer_list<T>& init_list) const;
	bool operator!=(std::initializer_list<T>& init_list) const;
	bool operator>=(std::initializer_list<T>& init_list) const;
	bool operator>(std::initializer_list<T>& init_list) const;
	bool operator<(std::initializer_list<T>& init_list) const;
	bool operator<=(std::initializer_list<T>& init_list) const;

	DynArr& operator+=(const DynArr& oth);
	DynArr& operator+=(const T& value);
	DynArr operator+(const DynArr& oth) const;
private:
	void Realloc(size_t new_cap);
private:
	size_t size = 0;
	size_t capacity = 0;
	int* data;
};

template<typename T>
DynArr<T>::DynArr(size_t len, const T& value)
{
	size = len;
	capacity = len;
	data = new T[len];
	std::fill(data, data + size, value);
}

template<typename T>
DynArr<T>::DynArr(const DynArr& oth)
{
	size = oth.size;
	capacity = oth.capacity;
	data = new T[capacity];
	std::copy(other.data, other.data + other.size, data);
}

template<typename T>
DynArr<T>::DynArr(const std::initializer_list<T>& init_list)
{
	size = init_list.size();
	capacity = init_list.size();
	data = new_int(capacity);
	std::copy(list.begin(), list.end(), data);
}

template<typename T>
const size_t DynArr<T>::Capacity()
{
	return capacity;
}

template<typename T>
const size_t DynArr<T>::Size()
{
	return size;
}

template<typename T>
int* DynArr<T>::Data() const
{
	return data;
}
