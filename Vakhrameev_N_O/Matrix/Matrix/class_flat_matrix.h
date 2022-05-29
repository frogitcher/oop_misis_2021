#pragma once
#include "class_matrix.h"

template<typename T>
class FlatMatrix : public BaseMatrix<T>
{
public:
	FlatMatrix(size_t r = 0, size_t c = 0, T value = T(0)); //done
	FlatMatrix(const FlatMatrix<T>& other); //done
	FlatMatrix(const std::initializer_list<std::initializer_list<T>>& list); //done
	~FlatMatrix(); //done

	void resize(size_t r, size_t c, T value = T(0)) override;//done
	T* operator[](size_t n) const; //done
	T& Get(size_t n, size_t m) const override; //done
	void diag(size_t n = 0, T value = T(0)) override; //done

	FlatMatrix<T>& operator=(const FlatMatrix<T>& other); //done
	FlatMatrix<T>& operator+=(const FlatMatrix<T>& other); //done
	FlatMatrix<T>& operator-=(const FlatMatrix<T>& other); //done
	FlatMatrix<T>& operator*=(const FlatMatrix<T>& other); //done
	FlatMatrix<T>& operator+=(const T& other); //done
	FlatMatrix<T>& operator-=(const T& other); //done
	FlatMatrix<T>& operator*=(const T& other); //done
	FlatMatrix<T> operator+(const FlatMatrix<T>& other) const; //done
	FlatMatrix<T> operator-(const FlatMatrix<T>& other) const; //done
	FlatMatrix<T> operator*(const FlatMatrix<T>& other) const; //done
	FlatMatrix<T> operator+(const T& other) const; //done
	FlatMatrix<T> operator-(const T& other) const; //done
	FlatMatrix<T> operator*(const T& other) const; //done

	bool operator==(const FlatMatrix<T>& other) const; //done
	bool operator!=(const FlatMatrix<T>& other) const; //done
private:
	T* data = nullptr;
};

template<typename T>
FlatMatrix<T>::FlatMatrix(size_t r, size_t c, T value)
	:BaseMatrix<T>(r, c)
{
	data = new T[r * c];
	std::fill(data, data + r * c, value);
}

template<typename T>
FlatMatrix<T>::~FlatMatrix() { delete[] data; };

template<typename T>
FlatMatrix<T>::FlatMatrix(const FlatMatrix<T>& other)
	: BaseMatrix<T>(other.rows, other.columns)
{
	data = new T[this->rows, this->columns];
	std::copy(other.data, other.data + other.rows * other.columns, data);
}

template<typename T>
FlatMatrix<T>::FlatMatrix(const std::initializer_list<std::initializer_list<T>>& list)
	: BaseMatrix<T>(list.size(), list.begin()->size())
{
	data = new T[this->rows * this->columns];
	std::fill(data, data + this->rows * this->columns, 0);
	for (int i = 0;i < this->rows;i++)
	{
		if ((list.begin() + i)->size() != this->columns)
		{
			throw std::logic_error("rows in intitalizer list should have the same size");
		}
		std::copy((list.begin() + i)->begin(), (list.begin() + i)->begin() + this->columns, data + i * this->columns);
	}
}

template<typename T>
void FlatMatrix<T>::resize(size_t r, size_t c, T value)
{
	delete[] data;
	data = new T[r * c];
	std::fill(data, data + r * c, value);
	this->rows = r;
	this->columns = c;
}

template<typename T>
T* FlatMatrix<T>::operator[](size_t n) const
{
	return data + n * this->columns;
}

template<typename T>
T& FlatMatrix<T>::Get(size_t n, size_t m) const
{
	if ((n >= this->rows) && (m >= this->columns))
	{
		throw std::out_of_range("indexes are out of range!");
	}
	return *(data + n * this->columns + m);
}

template<typename T>
void FlatMatrix<T>::diag(size_t n, T value)
{
	resize(n, n,T(0));
	int t = 0;
	for (int i = 0;i < n * n;i += n)
	{
		data[i + t] = value;
		t++;
	}
}

template<typename T>
FlatMatrix<T>& FlatMatrix<T>::operator+=(const FlatMatrix<T>& other)
{
	if (this->rows != other.rows || this->columns != other.columns)
	{
		throw std::logic_error("sizes of matrixes are not equal");
	}
	else
	{
		for (int i = 0;i < this->rows * this->columns;i++)
		{
			data[i] += other.data[i];
		}
		return *this;
	}
}

template<typename T>
FlatMatrix<T>& FlatMatrix<T>::operator-=(const FlatMatrix<T>& other)
{
	if (this->rows != other.rows || this->columns != other.columns)
	{
		throw std::logic_error("sizes of matrixes are not equal");
	}
	else
	{
		for (int i = 0;i < this->rows*this->columns;i++)
		{
			data[i]-=other.data[i];
		}
		return *this;
	}
}

template<typename T>
FlatMatrix<T>& FlatMatrix<T>::operator*=(const FlatMatrix<T>& other)
{
	if (this->columns != other.rows)
	{
		throw std::logic_error("can not multiply two matrixes");
	}
	else
	{
		T* c = new T[this->rows * other.columns];
		std::fill(c,c+this->rows*this->columns,T(0));
		for (int i = 0;i < this->rows;i++)
		{
			for (int j = 0;j < other.columns;j++)
			{
				for (int k = 0;k < this->columns;k++)
				{
					c[i * this->rows + j] += other.Get(i, k) * Get(k, j);
				}
			}
		}
		this->columns = other.columns;
		for (int i = 0;i < this->rows * this->columns;i++)
		{
			data[i] = c[i];
		}
		delete[] c;
		return *this;
	}
}

template<typename T>
FlatMatrix<T> FlatMatrix<T>::operator-(const FlatMatrix<T>& other) const
{
	if (this->rows != other.rows || this->columns != other.columns)
	{
		throw std::logic_error("sizes of matrixes are not equal");
	}
	return FlatMatrix<T>(*this) -= other;
}

template<typename T>
FlatMatrix<T> FlatMatrix<T>::operator+(const FlatMatrix<T>& other) const
{
	if (this->rows != other.rows || this->columns != other.columns)
	{
		throw std::logic_error("sizes of matrixes are not equal");
	}
	return FlatMatrix<T>(*this) += other;
}

template<typename T>
FlatMatrix<T> FlatMatrix<T>::operator*(const FlatMatrix<T>& other) const
{
	if (this->columns != other.rows)
	{
		throw std::logic_error("can not multiply two matrixes");
	}
	return FlatMatrix<T>(*this) *= other;
}

template<typename T>
FlatMatrix<T>& FlatMatrix<T>::operator+=(const T& other)
{
	if (this->is_square())
	{
		FlatMatrix<T> temp(this->rows);
		temp.diag(temp.get_rows(), other);
		return *this += temp;
	}
	else
	{
		throw std::logic_error("marix should be square");
	}
}

template<typename T>
FlatMatrix<T>& FlatMatrix<T>::operator-=(const T& other)
{
	if (this->is_square())
	{
		FlatMatrix<T> temp(this->rows);
		temp.diag(temp.get_rows(), other);
		return *this -= temp;
	}
	else
	{
		throw std::logic_error("marix should be square");
	}
}

template<typename T>
FlatMatrix<T>& FlatMatrix<T>::operator*=(const T& other)
{
	for (int i = 0;i < this->rows*this->rows;i++)
	{
		data[i]*=other;
	}
	return *this;
}

template<typename T>
FlatMatrix<T> FlatMatrix<T>::operator+(const T& other) const
{
	return FlatMatrix(*this) += other;
}

template<typename T>
FlatMatrix<T> FlatMatrix<T>::operator-(const T& other) const
{
	return FlatMatrix(*this) -= other;
}

template<typename T>
FlatMatrix<T> FlatMatrix<T>::operator*(const T& other) const
{
	return FlatMatrix(*this) *= other;
}

template<typename T>
bool FlatMatrix<T>::operator==(const FlatMatrix<T>& other) const
{
    return std::equal(data,data+this->rows*this->columns,other.data,other.data+other.rows*other.columns);
}

template<typename T>
bool FlatMatrix<T>::operator!=(const FlatMatrix<T>& other) const
{
    return !((*this)==other);
}

template<typename T>
FlatMatrix<T>& FlatMatrix<T>::operator=(const FlatMatrix<T>& other)
{
    resize(other.rows,other.columns,T(0));
    std::copy(other.data,other.data+other.rows*other.columns,data);
    return *this;
}
