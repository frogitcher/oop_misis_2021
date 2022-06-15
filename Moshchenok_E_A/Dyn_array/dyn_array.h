#pragma once
#include <memory>
#include <initializer_list>

template<typename T>
class it {
public:
	it(T** p, const std::size_t _id);
	T& operator*();
	T* operator+(const int rhs);
	T* operator-(const int rhs);
	bool operator==(const it<T>& rhs) const;
	bool operator==(const T* rhs) const;
	bool operator!=(const it<T>& rhs) const;
private:
	T** ptr;
	std::size_t id;
};

template<typename T>
it<T>::it(T** p, const std::size_t _id) {
	ptr = p;
	id = _id;
}

template<typename T>
T& it<T>::operator*() {
	return *(*ptr + id);
}

template<typename T>
T* it<T>::operator+(const int rhs) {
	return *ptr + id + rhs;
}

template<typename T>
T* it<T>::operator-(const int rhs) {
	return *ptr + (-rhs);
}

template<typename T>
bool it<T>::operator==(const it<T>& rhs) const{
	return ptr == rhs.ptr && id == rhs.id;
}

template<typename T>
bool it<T>::operator==(const T* rhs) const{
	return *ptr + id == rhs;
}

template<typename T>
bool it<T>::operator!=(const it<T>& rhs) const{
	return !(ptr == rhs.ptr);
}


template<typename T>
class Dyn_array {
public:
	Dyn_array();
	Dyn_array(const std::size_t _size, const T val);
	Dyn_array(const Dyn_array<T>& other);
	Dyn_array(const std::initializer_list<T>& list);
	~Dyn_array();

	T& operator[](const std::size_t id) const;
	Dyn_array<T>& operator=(const Dyn_array<T>& rhs);
	bool operator==(const Dyn_array<T>& rhs) const;
	bool operator!=(const Dyn_array<T>& rhs) const;
	
	void resize(const std::size_t _size);
	void resize(const std::size_t _size, const T& val);
	void insert(const std::size_t id, const T& val);
	void erase(const std::size_t id);
	void push_back(const T& val);
	void pop_back();
	void push_front(const T& val);
	void pop_front();
	void reverse();
	void clear();
	void swap(Dyn_array& other);
	void assign(const std::size_t _size, const T& val);
	void assign(const T* new_data_begin, const T* new_data_end);
	void assign(const std::initializer_list<T>& list);
	std::size_t size() const;
	std::size_t capacity() const;
	bool empty() const;
	it<T> begin();
	it<T> end();
	T& at(const std::size_t id) const;

private:
	std::size_t size_;
	std::size_t capacity_;
	T* data;
	void reallocate(const std::size_t new_size);
};

template<typename T>
Dyn_array<T>::Dyn_array() {
	size_ = 0;
	capacity_ = 1;
	data = new T[capacity_];
}

template<typename T>
Dyn_array<T>::Dyn_array(const std::size_t _size, const T val) {
	size_ = _size;
	capacity_ = _size;
	data = new T[size_];
	std::fill(data, data + size_, val);
}

template<typename T>
Dyn_array<T>::Dyn_array(const Dyn_array<T>& other) {
	size_ = other.size_;
	capacity_ = other.size_;
	data = new T[size_];
	std::copy(other.data, other.data + other.size_, data);
}

template<typename T>
Dyn_array<T>::Dyn_array(const std::initializer_list<T>& list) {
	size_ = list.size();
	capacity_ = list.size();
	data = new T[size_];
	std::copy(list.begin(), list.end() + list.size(), data);
}

template<typename T>
Dyn_array<T>::~Dyn_array() {
	delete[] data;
}

template<typename T>
T& Dyn_array<T>::operator[](const std::size_t id) const {
	if (id >= size_)
		throw std::out_of_range("Out of range");
	return *(data + id);
}

template<typename T>
Dyn_array<T>& Dyn_array<T>::operator=(const Dyn_array<T>& rhs) {
	this->resize(rhs.size_);
	std::copy(rhs.data, rhs.data + rhs.size_, data);
	return *this;
}

template<typename T>
bool Dyn_array<T>::operator==(const Dyn_array<T>& rhs) const{
	if (size_ != rhs.size_)
		return false;
	size_t i = 0;
	while(i < size_ && (*this)[i] == rhs[i])
		i++;
	return i == size_;
}

template<typename T>
bool Dyn_array<T>::operator!=(const Dyn_array<T>& rhs) const {
	return !(*this == rhs);
}

template<typename T>
void Dyn_array<T>::reallocate(const std::size_t new_size) {
	while (capacity_ < new_size)
		capacity_ *= 2;
	T* new_data = new T[capacity_];
	std::copy(data, data + size_, new_data);
	delete[] data;
	data = new_data;
	size_ = new_size;
}

template<typename T>
void Dyn_array<T>::resize(const std::size_t new_size) {
	if (new_size <= capacity_) {
		size_ = new_size;
	} else {
		this->reallocate(new_size);
	}
}

template<typename T>
void Dyn_array<T>::resize(const std::size_t new_size, const T& val) {
	if (new_size <= capacity_) {
		if (new_size > size_)
			std::fill(data + size_, data + new_size, val);
		size_ = new_size;
	} else {
		std::size_t old = size_;
		this->reallocate(new_size);
		std::fill(data + old, data + size_, val);
	}
}

template<typename T>
void Dyn_array<T>::insert(const std::size_t id, const T& val) {
	if (id > size_)
		throw std::out_of_range("Out of range");
	this->resize(size_ + 1);
	for (std::size_t i = size_ - 1; i > id; --i) {
		(*this)[i] = (*this)[i - 1];
	}
	(*this)[id] = val;
}

template<typename T>
void Dyn_array<T>::erase(const std::size_t id) {
	if (id >= size_)
		throw std::out_of_range("Out of range");
	for (std::size_t i = id; i + 1 < size_; ++i) {
		(*this)[i] = (*this)[i + 1];
	}
	this->resize(size_ - 1);
}

template<typename T>
void Dyn_array<T>::push_back(const T& val) {
	this->resize(size_ + 1, val);
}

template<typename T>
void Dyn_array<T>::pop_back() {
	this->resize(size_ - 1);
}

template<typename T>
void Dyn_array<T>::push_front(const T& val) {
	this->insert(0, val);
}

template<typename T>
void Dyn_array<T>::pop_front() {
	this->erase(0);
}

template<typename T>
void Dyn_array<T>::reverse() {
	if (size_ > 0) {
		std::size_t l = 0;
		std::size_t r = size_ - 1;
		for (;l < r; ++l, --r) {
			T x = (*this)[l];
			(*this)[l] = (*this)[r];
			(*this)[r] = x; 
		}
	}
}

template<typename T>
void Dyn_array<T>::clear() {
	size_ = 0;
}

template<typename T>
void Dyn_array<T>::swap(Dyn_array& other) {
	std::swap(data, other.data);
	std::swap(size_, other.size_);
	std::swap(capacity_, other.capacity_);
}

template<typename T>
void Dyn_array<T>::assign(const std::size_t new_size, const T& val) {
	this->resize(new_size);
	std::fill(data, data + size_, val);
}

template<typename T>
void Dyn_array<T>::assign(const T* new_data_begin, const T* new_data_end) {
	this->resize(new_data_end - new_data_begin);
	std::copy(new_data_begin, new_data_end, data);
}

template<typename T>
void Dyn_array<T>::assign(const std::initializer_list<T>& list) {
	this->resize(list.size());
	std::copy(list.begin(), list.end(), data);
}

template<typename T>
std::size_t Dyn_array<T>::size() const {
	return size_;
}

template<typename T>
std::size_t Dyn_array<T>::capacity() const {
	return capacity_;
}

template<typename T>
bool Dyn_array<T>::empty() const {
	return size_ == 0;
}

template<typename T>
it<T> Dyn_array<T>::begin() {
	return it<T>(&data, 0);
}

template<typename T>
it<T> Dyn_array<T>::end() {
	return it<T>(&data, size_);
}

template<typename T>
T& Dyn_array<T>::at(const std::size_t id) const {
	if (id >= size_)
		throw std::out_of_range("Out of range");
	return (*this)[id];
}

