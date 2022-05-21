#pragma once
#include <initializer_list>
#include <stdexcept>
#include <algorithm>

template<size_t Size>
class Vector
{
public:
	Vector<Size>(const double value = 0.0) noexcept;
	Vector<Size>(const std::initializer_list<double>& list);
	Vector<Size>(const Vector<Size>& oth);
	~Vector<Size>();

	double& At(const size_t idx) const;
	double& operator[](const size_t idx) const;

	Vector<Size>& operator+=(const Vector<Size>& oth);
	Vector<Size> operator+(const Vector<Size>& oth) const;
	Vector<Size>& operator-=(const Vector<Size>& oth);
	Vector<Size> operator-(const Vector<Size>& oth) const;
	Vector<Size>& operator*=(const int num);
	Vector<Size> operator*(const int num) const;
	double operator*(const Vector<Size>& oth) const;

	void operator=(const Vector<Size>& oth);
	bool operator==(const Vector<Size>& oth) const noexcept;
	bool operator!=(const Vector<Size>& oth) const noexcept;

	double Norm() const noexcept;
private:
	double* data = nullptr;
	int size = 0;
};

template<size_t Size>
Vector<Size>::Vector(const double value) noexcept : size(Size)
{
	data = new double[size];
	std::fill(data, data + size, value);
}

template<size_t Size>
Vector<Size>::Vector(const std::initializer_list<double>& list) : size(Size)
{
	if (Size != list.size()) {
		throw std::invalid_argument("Template for Vector and list size are not equal!");
	}
	data = new double[size];
	int i = 0;
	for (const auto l : list) {
		data[i] = l;
		++i;
	}
}

template<size_t Size>
Vector<Size>::Vector(const Vector<Size>& oth) : size(Size)
{
	if (Size != oth.size()) {
		throw std::invalid_argument("Template for Vector and size of given Vector are not equal!");
	}
	data = new double[size];
	std::copy(oth.data, oth.data + size, data);
}

template<size_t Size>
Vector<Size>::~Vector()
{
	delete[] data;
}

template<size_t Size>
double& Vector<Size>::At(const size_t idx) const
{
	if (idx >= size) {
		throw std::out_of_range("Index is out of range!");
	}
	return *(data + idx);
}

template<size_t Size>
double& Vector<Size>::operator[](const size_t idx) const
{
	if (idx >= size) {
		throw std::out_of_range("Index is out of range!");
	}
	return data[idx];
}

template<size_t Size>
Vector<Size>& Vector<Size>::operator+=(const Vector<Size>& oth)
{
	if (size != oth.size) {
		throw std::invalid_argument("Cannot perform += operation with vectors of different dimentions!");
	}
	for (int i = 0; i < size; ++i) {
		data[i] += oth[i];
	}
	return *this;
}

template<size_t Size>
Vector<Size> Vector<Size>::operator+(const Vector<Size>& oth) const
{
	Vector<size> res(this);
	return res += oth;
}

template<size_t Size>
Vector<Size>& Vector<Size>::operator-=(const Vector<Size>& oth)
{
	if (size != oth.size) {
		throw std::invalid_argument("Cannot perform += operation with vectors of different dimentions!");
	}
	for (int i = 0; i < size; ++i) {
		data[i] -= oth[i];
	}
	return *this;
}

template<size_t Size>
Vector<Size> Vector<Size>::operator-(const Vector<Size>& oth) const
{
	Vector<size> res(this);
	return res -= oth;
}

template<size_t Size>
Vector<Size>& Vector<Size>::operator*=(const int num)
{
	for (int i = 0; i < size; ++i) {
		data[i] *= num;
	}
	return *this;
}

template<size_t Size>
Vector<Size> Vector<Size>::operator*(const int num) const
{
	Vector<size> res(this);
	return res *= num;
}

template<size_t Size>
double Vector<Size>::operator*(const Vector<Size>& oth) const
{
	if (size != oth.size) {
		throw std::invalid_argument("Cannot perform scalar multiplication with Vectors of different size");
	}
	double res = 0.0;
	for (int i = 0; i < size; ++i) {
		res += data[i] * oth[i];
	}
	return res;
}

template<size_t Size>
void Vector<Size>::operator=(const Vector<Size>& oth)
{
	if (size != oth.size) {
		throw std::invalid_argument("Cannot perform operator= with vectors of different dimentions!");
	}
	std::copy(oth.data, oth.data + size, data);
}

template<size_t Size>
bool Vector<Size>::operator==(const Vector<Size>& oth) const noexcept
{
	if (size != oth.size) {
		return false;
	}
	for (int i = 0; i < size; ++i) {
		if (data[i] != oth[i]) {
			return false;
		}
	}
	return true;
}

template<size_t Size>
bool Vector<Size>::operator!=(const Vector<Size>& oth) const noexcept
{
	return !(*this == oth);
}

template<size_t Size>
double Vector<Size>::Norm() const noexcept
{
	double norm = 0.0;
	for (int i = 0; i < size; ++i) {
		norm += data[i] * data[i];
	}
	return sqrt(norm);
}
