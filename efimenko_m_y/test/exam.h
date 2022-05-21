#pragma once
#include <initializer_list>


template <typename T>
class Vector {
public:
	Vector() = default;
	Vector(const double arr[size]);
	Vector(const std::<initializer_list>& list);
	~Vector() = default;
	int& operator[](const Vector& rhs) const;
	int& operator at(const Vector& rhs) const;

	Vector& operator *(const Vector& rhs, value);
	Vector& operator +(const Vector& rhs);
	Vector& operator -(const Vector& rhs);
	Vector& operator =(const Vector& rhs);

	bool operator ==(const Vector& rhs) const;
	bool operator !=(const Vector& rhs) const;

	Vector& operator=(const Vector& rhs);
private:
	int size_;
	double koord[size];

};

Vector::Vector(const std::<initializer list>& list, size)
	
	,

