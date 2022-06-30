#pragma once
#include "matrix.h"


template<typename T>

class Flat:public Base<T> {
public:
	Flat(size_t r , size_t c, T value = (T));
	T* operator[](size_t r) const override;
	Flat(const Flat<T>& other);
	Flat(std::initializer_list<std::initializer_list<T>> list);
	Flat() = default;
	~Flat();

	void Del() override;
	void Resize(size_t n_r, size_t n_c, T value = (T)0) override;
	T& Get(size_t n_r, size_t n_c ) const override;

	bool operator==(const Flat < T>& other) const;
	bool operator!=(const Flat < T>& other) const;

	Flat<T> operator +(const Flat<T>& other) const;
	Flat<T> operator -(const Flat<T>& other) const;
	Flat<T> operator *(const Flat<T>& other) const;
	Flat<T>& operator =(const Flat<T>& other);

	Flat<T>& operator +=(const Flat<T>& other);
	Flat<T>& operator -=(const Flat<T>& other);
	Flat<T>& operator *=(const Flat<T>& other);
private:
	T* data = nullptr;

};



template<typename T>
Flat<T>::Flat(size_t r, size_t c, T value ): Base<T>(r,c), data(new T[r * c]) {
	std::fill(data, data + (r * c), value);
}

template<typename T>
T* Flat<T>::operator[](size_t r) const {
	return (data + this->n_c * r);
}

template<typename T>
Flat<T>::Flat(const Flat<T>& other): Base<T>(other.n_r,other.n_c){
	*this= other;
}

template<typename T>
Flat<T>::Flat(std::initializer_list<std::initializer_list<T>> list) : Base<T>(list.size(), list.begin()->size()){
	data = new T[this->n_r * this->n_c];
	for (int i = 0;i < list.size();i++) {
		if ((list.begin() + i)->size() != this->n_c) {
			delete[] data;
			std::invalid_argument("There is no such matrix");
		}
		std::copy((list.begin() + i)->begin(), (list.begin() + i)->begin() + this->n_c, data + i * this->n_c);
	}

}

template<typename T>
Flat<T>::~Flat() {
	Del();
}

template<typename T>
void Flat<T>::Del() {
	Base<T>::n_r = 0;
	Base<T>::n_c = 0;
	delete[] data;
}


template<typename T>
void Flat<T>::Resize(size_t r, size_t c, T value) {
	*this = Flat<T>(r, c, value);
}

template<typename T>
T& Flat<T>::Get(size_t r, size_t c) const {
	if (this->n_r > r && this->n_c > c) {
		return data[this->n_r * r + c];
	} 
	throw std::out_of_range("chel ti v mute");
}



template<typename T>
Flat<T>& Flat<T>::operator=(const Flat<T>& other) {
	data = new T[other.n_r* other.n_c];
	std::copy(other.data, other.data + other.n_r * other.n_c, data);
	this->n_r = other.n_r;
	this->n_c = other.n_c;
	return *this;
}


template<typename T>
bool Flat<T>::operator==(const Flat<T>& other) const {
	return (this->n_r == other.n_r && this->n_c == other.n_c && std::equal(data, data + this->n_r * this->n_c, other.data));
}

template<typename T>
bool Flat<T>::operator!=(const Flat<T>& other) const {
	return !(*this==other);
}

template<typename T>
Flat<T>& Flat<T>::operator +=(const Flat<T>& other)  {
	if (this->n_r == other.n_r && this->n_c == other.n_c) {
		for (int i = 0;i < this->n_r * this->n_c;i++) {
			data[i] += other.data[i];
		}
		return *this;
	}
	throw std::invalid_argument("impossible");
}

template<typename T>
Flat<T>& Flat<T>::operator -=(const Flat<T>& other) {
	if (this->n_r == other.n_r && this->n_c == other.n_c) {
		for (int i = 0;i < this->n_r * this->n_c;i++) {
			data[i] -= other.data[i];
		}
		return *this;
	}
	throw std::invalid_argument("impossible");
}


template<typename T>
Flat<T>& Flat<T>::operator *=(const Flat<T>& other) {
	if (this->n_ñ == other.n_r) {
		T* new_data = new T[this->n_r * other.n_c];
		for (int i = 0; i < this->n_r; i++) {
			for (int j = 0; j < other.n_c; j++) {
				for (int k = 0; k < other.n_r; k++) {
					new_data[i * other.n_c + j] += Get(i, k) * other.Get(k, j);
				}
			}
		}
		delete[] data;
		data = new_data;
	}
	else {
		throw std::invalid_argument("impossible");
	}
	this->n_c = other.n_c;
}

template<typename T>
Flat<T> Flat<T>::operator+(const Flat<T>& other) const {
	return Flat<T>(*this) += other;
}

template<typename T>
Flat<T> Flat<T>::operator-(const Flat<T>& other) const {
	return Flat<T>(*this) -= other;
}

template<typename T>
Flat<T> Flat<T>::operator*(const Flat<T>& other) const {
	return Flat<T>(*this) *= other;
}