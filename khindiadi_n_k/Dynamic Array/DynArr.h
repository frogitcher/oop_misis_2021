#pragma once

#include <initializer_list>
#include <stdexcept>

template<typename T>
class DynArr
{
public:
	DynArr(size_t len = 0, const T& value = 0);
	DynArr(const DynArr& oth);
	DynArr(const std::initializer_list<T>& init_list);
	~DynArr();
	inline size_t Capacity() const;
	inline size_t Size() const;
	inline T* Data() const;
	void Push_back(const T& value);
	void Push_back(const DynArr<T>& oth);
	void Push_front(const T& value);
	void Push_front(const DynArr<T>& oth);
	void Pop_back();
	void Pop_front();
	inline bool Empty() const;
	void Erase(size_t start_idx, int amount = 1);
	void Insert(size_t idx, const T& value);
	void Clear();
	T& At(const size_t idx) const;
	void Assign(size_t new_size, const T& value);
	void Resize(size_t new_size, const T& value = T());
	void Swap(DynArr& other);
	inline void SwapItemsAt(const size_t i, const size_t j);
	inline T* Begin() const;
	inline T* End() const;
	inline T& Back() const;
	inline T& Front() const;
	DynArr<T> SubArr(size_t first_idx, size_t last_idx); //Last idx is included, so it cannot be >= size
	void ReplaceAll(const T& key, const T& value);
	void EraseIf(const T& key);
	void Reverse();
	bool Contains(const T& key) const;
	int Count(const T& key) const;

	DynArr<T>& operator=(const DynArr& oth);
	inline T& operator[](size_t i) const;

	bool operator==(const DynArr& oth) const;
	bool operator!=(const DynArr& oth) const;
	bool operator>=(const DynArr& oth) const;
	bool operator>(const DynArr& oth) const;
	bool operator<(const DynArr& oth) const;
	bool operator<=(const DynArr& oth) const;

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
	T* Alloc(size_t cap) const;
	inline void DeleteData();
	void Realloc(size_t cap);
private:
	size_t size = 0;
	size_t capacity = 0;
	T* data;
};

template<typename T>
T* DynArr<T>::Alloc(size_t cap) const
{
	return new T[cap];
}

template<typename T>
inline void DynArr<T>::DeleteData()
{
	delete[] data;
}

template<typename T>
void DynArr<T>::Realloc(size_t cap)
{
	T* new_data = Alloc(cap);
	std::copy(data, data + size, new_data);
	DeleteData();
	data = new_data;
	capacity = cap;
}

template<typename T>
DynArr<T>::DynArr(size_t len, const T& value)
{
	size = len;
	capacity = len;
	data = Alloc(len);
	std::fill(data, data + size, value);
}

template<typename T>
DynArr<T>::DynArr(const DynArr& oth)
{
	size = oth.size;
	capacity = oth.capacity;
	data = Alloc(capacity);
	std::copy(oth.data, oth.data + oth.size, data);
}

template<typename T>
DynArr<T>::DynArr(const std::initializer_list<T>& init_list)
{
	size = init_list.size();
	capacity = init_list.size();
	data = Alloc(capacity);
	std::copy(init_list.begin(), init_list.end(), data);
}

template<typename T>
DynArr<T>::~DynArr()
{
	DeleteData();
}

template<typename T>
inline size_t DynArr<T>::Capacity() const
{
	return capacity;
}

template<typename T>
inline size_t DynArr<T>::Size() const
{
	return size;
}

template<typename T>
inline T* DynArr<T>::Data() const
{
	return data;
}

template<typename T>
void DynArr<T>::Push_back(const T& value)
{
	if (size == capacity) {
		Realloc(capacity ? capacity * 2 : 1);
	}
	data[size] = value;
	++size;
}

template<typename T>
void DynArr<T>::Push_back(const DynArr<T>& oth)
{
	if (oth.Empty()) {
		return;
	}
	size_t new_size = size + oth.size;
	if (new_size >= capacity) {
		Realloc(new_size * 2);
	}
	std::copy(oth.data, oth.data + oth.size, data + size);
	size = new_size;
}

template<typename T>
void DynArr<T>::Push_front(const T& value)
{
	if (size == capacity) {
		int new_capacity = capacity ? capacity * 2 : 1;
		T* new_data = Alloc(new_capacity);
		capacity = new_capacity;
		std::copy(data, data + size, new_data + 1);
		DeleteData();
		data = new_data;
	}
        else{
	        std::copy(data, data + size, data + 1);
	} 
        data[0] = value;
	++size;
}

template<typename T>
void DynArr<T>::Push_front(const DynArr<T>& oth)
{
	if (oth.Empty()) {
		return;
	}
	size_t new_size = size + oth.size;
	if (new_size >= capacity) {
		int new_capacity = new_size * 2;
		T* new_data = Alloc(new_capacity);
		capacity = new_capacity;
		std::copy(data, data + size, new_data + oth.size);
		std::copy(oth.data, oth.data + oth.size, new_data);
		DeleteData();
		data = new_data;
	}
	else {
		std::copy(data, data + size, data + oth.size);
		std::copy(oth.data, oth.data + oth.size, data);
	}
	size = new_size;
}

template<typename T>
void DynArr<T>::Pop_back()
{
	if (size == 0) {
		throw std::out_of_range("Cannot pop last element from an empty array");
	}
	--size;
}

template<typename T>
void DynArr<T>::Pop_front()
{
	if (size == 0) {
		throw std::out_of_range("Cannot pop first element from an empty array");
	}
	else if (size == 1) {
		size = 0;
		return;
	}
	std::copy(data + 1, data + size, data);
	--size;
}

template<typename T>
inline bool DynArr<T>::Empty() const
{
	return size == 0;
}

template<typename T>
void DynArr<T>::Erase(size_t start_idx, int amount)
{
	if (start_idx + amount > size) {
		throw std::out_of_range("Last array index is lower than last provided index to erase");
	}
	if (amount < 0) {
		throw std::invalid_argument("Cannot erase negative amount of items");
	}

	//Amount == 0 does not cause an exception, it just does senseless iterations

	size_t start_idx_dub = start_idx;
	for (int i = start_idx + amount; i < (int)size; ++i) {
		*(data + start_idx_dub) = *(data + i);
		++start_idx_dub;
	}
	size -= amount;
}

template<typename T>
void DynArr<T>::Insert(size_t idx, const T& value)
{
	if (idx > size) {
		throw std::out_of_range("Cannot perform insertion - provided index is out of range");
	}
	else if (idx == size) {
		Push_back(value);
		return;
	}
	for (size_t i = size - 1; i > idx; i--) {
		data[i] = data[i - 1];
	}
	data[idx] = value;
	++size;
}

template<typename T>
void DynArr<T>::Clear()
{
	size = 0;
}

template<typename T>
T& DynArr<T>::At(const size_t idx) const
{
	if (idx >= size) {
		throw std::out_of_range("Index is out of range");
	}
	return data[idx];
}

template<typename T>
void DynArr<T>::Assign(size_t new_size, const T& value)
{
	if (new_size >= capacity) {
		T* new_data = Alloc(new_size * 2);
		capacity = new_size * 2;
		DeleteData();
                data = new_data;
	}
	size = new_size;
	std::fill(data, data + size, value);
}

template<typename T>
void DynArr<T>::Resize(size_t new_size, const T& value)
{
	if (new_size < size) {
		size = new_size;
		return;
	}
	DynArr tmp(new_size - size, value);
	Push_back(tmp);
}

template<typename T>
void DynArr<T>::Swap(DynArr& oth)
{
	std::swap(data, oth.data);
	std::swap(capacity, oth.capacity);
	std::swap(size, oth.size);
}

template<typename T>
inline void DynArr<T>::SwapItemsAt(const size_t i, const size_t j)
{
	std::swap(data[i], data[j]);
}

template<typename T>
inline T* DynArr<T>::Begin() const
{
	return data;
}

template<typename T>
inline T* DynArr<T>::End() const
{
	return data + size;
}

template<typename T>
inline T& DynArr<T>::Back() const
{
	if (size == 0) {
		throw std::out_of_range("Cannot get last element of an empty array");
	}
	return data[size - 1];
}

template<typename T>
inline T& DynArr<T>::Front() const
{
	if (size == 0) {
		throw std::out_of_range("Cannot get first element of an empty array");
	}
	return data[0];
}

template<typename T>
DynArr<T> DynArr<T>::SubArr(size_t first_idx, size_t last_idx)
{
	if (last_idx < first_idx) {
		throw std::invalid_argument("Last indext of sub-array cannot be less than first");
	}
	if (last_idx >= size) {
		throw std::out_of_range("Given sub-array borders are out of parent array range");
	}

	DynArr<T> subArr;
	for (int i = first_idx; i <= (int)last_idx; ++i) {
		subArr.Push_back(data[i]);
	}

	return subArr;
}

template<typename T>
void DynArr<T>::ReplaceAll(const T& key, const T& value)
{
	for (int i = 0; i < (int)size; ++i) {
		if (data[i] == key) {
			data[i] = value;
		}
	}
}

template<typename T>
void DynArr<T>::EraseIf(const T& key)
{
	for (int i = 0; i < (int)size; ++i) {
		if (data[i] == key) {
			Erase(i);
			--i;
		}
	}
}

template<typename T>
void DynArr<T>::Reverse()
{
	for (int i = 0; i < size / 2; ++i) {
		std::swap(data[i], data[size - i - 1]);
	}
}

template<typename T>
bool DynArr<T>::Contains(const T& key) const
{
	for (int i = 0; i < size; ++i) {
		if (data[i] == key) {
			return true;
		}
	}
	return false;
}

template<typename T>
inline int DynArr<T>::Count(const T& key) const
{
	int cnt = 0;
	for (int i = 0; i < size; ++i) {
		if (data[i] == key) {
			cnt++;
		}
	}
	return cnt;
}

template<typename T>
DynArr<T>& DynArr<T>::operator=(const DynArr& oth)
{
	if (oth.size > capacity) {
		DeleteData();
		capacity = oth.capacity;
		data = Alloc(capacity);
	}
	size = oth.size;
	std::copy(oth.data, (oth.data + oth.size), data);
	return *this;
}

template<typename T>
inline T& DynArr<T>::operator[](size_t i) const
{
	return data[i];
}

template<typename T>
bool DynArr<T>::operator==(const DynArr& oth) const
{
	return std::equal(Begin(), End(), oth.Begin());
}

template<typename T>
bool DynArr<T>::operator!=(const DynArr& oth) const
{
	return !(*this == oth);
}

template<typename T>
bool DynArr<T>::operator>=(const DynArr& oth) const
{
	return !(*this < oth);
}

template<typename T>
bool DynArr<T>::operator>(const DynArr& oth) const
{
	return oth < *this;
}

template<typename T>
bool DynArr<T>::operator<(const DynArr& oth) const
{
	for (int i = 0; i < std::min(size, oth.size); ++i) {
		if (data[i] == oth.data[i]) {
			continue;
		}
		return data[i] < oth.data[i];
	}
	return size < oth.size;
}

template<typename T>
bool DynArr<T>::operator<=(const DynArr& oth) const
{
	return !(*this > oth);
}

template<typename T>
bool DynArr<T>::operator==(std::initializer_list<T>& init_list) const
{
	return *this == DynArr(init_list);
}

template<typename T>
bool DynArr<T>::operator!=(std::initializer_list<T>& init_list) const
{
	return *this != DynArr(init_list);
}

template<typename T>
bool DynArr<T>::operator>=(std::initializer_list<T>& init_list) const
{
	return *this >= DynArr(init_list);
}

template<typename T>
bool DynArr<T>::operator>(std::initializer_list<T>& init_list) const
{
	return *this > DynArr(init_list);
}

template<typename T>
bool DynArr<T>::operator<(std::initializer_list<T>& init_list) const
{
	return *this < DynArr(init_list);
}

template<typename T>
bool DynArr<T>::operator<=(std::initializer_list<T>& init_list) const
{
	return *this <= DynArr(init_list);
}

template<typename T>
DynArr<T>& DynArr<T>::operator+=(const DynArr<T>& oth)
{
	Push_back(oth);
	return *this;
}

template<typename T>
DynArr<T>& DynArr<T>::operator+=(const T& value)
{
	Push_back(value);
	return *this;
}

template<typename T>
DynArr<T> DynArr<T>::operator+(const DynArr& oth) const
{
	return DynArr(*this) += oth;
}