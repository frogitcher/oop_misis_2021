#include "class_matrix.h"
template<typename T>
class TableMatrix : public BaseMatrix<T>
{
public:
	TableMatrix(size_t r = 0, size_t c = 0, T value = T(0)); //done
	TableMatrix(const std::initializer_list<std::initializer_list<T>>& list); //done
	TableMatrix(const TableMatrix& other); //done
	~TableMatrix(); //done

	void resize(size_t r = 0, size_t c = 0, T value = T(0)) override; //doee
	T* operator[](size_t n); //done
	T& Get(size_t n, size_t m) const override; //done
	void diag(size_t n = 0, T value = T(0)) override;

	TableMatrix<T>& operator=(const TableMatrix<T>& other);
	TableMatrix<T>& operator+=(const TableMatrix<T> other);
	TableMatrix<T>& operator-=(const TableMatrix<T> other);
	TableMatrix<T>& operator*=(const TableMatrix<T> other);
	TableMatrix<T>& operator+=(T other);
	TableMatrix<T>& operator-=(T other);
	TableMatrix<T>& operator*=(T other);
	TableMatrix<T> operator+(const TableMatrix<T> other) const;
	TableMatrix<T> operator-(const TableMatrix<T> other) const;
	TableMatrix<T> operator*(const TableMatrix<T> other) const;
	TableMatrix<T> operator+(T other) const;
	TableMatrix<T> operator-(T other) const;
	TableMatrix<T> operator*(T other) const;

	bool operator==(const TableMatrix<T>& other) const;
	bool operator!=(const TableMatrix<T>& other) const;

private:
	T** data = nullptr;
};


template<typename T>
TableMatrix<T>::TableMatrix(size_t r, size_t c, T value)
	: BaseMatrix<T>(r, c)
{
	data = new T * [r];
	for (int i = 0;i < this->rows;i++)
	{
		data[i] = new T[c];
		std::fill(data[i], data[i] + c, value);
	}
}

template<typename T>
TableMatrix<T>::TableMatrix(const TableMatrix<T>& other)
	:BaseMatrix<T>(other.rows, other.columns)
{
	data = new T * [this->rows];
	for (int i = 0;i < this->rows;i++)
	{
		data[i] = new T[this->columns];
		std::copy(other.data[i], other.data[i] + this->columns, data[i]);
	}
}

template<typename T>
TableMatrix<T>::TableMatrix(const std::initializer_list<std::initializer_list<T>>& list)
	:BaseMatrix<T>(list.size(), list.begin()->size())
{
	data = new T * [this->rows];
	for (int i = 0;i < this->rows;i++)
	{
		data[i] = new T[this->columns];
		std::fill(data[i], data[i] + this->columns, 0);
	}
	for (int i = 0;i < this->rows;i++)
	{
		if ((list.begin() + i)->size() != this->columns)
		{
			throw std::logic_error("rows in intitalizer list should have the same size");
		}
		std::copy((list.begin() + i)->begin(), (list.begin() + i)->begin() + this->columns, data[i]);
	}
}

template<typename T>
TableMatrix<T>::~TableMatrix()
{
	for (int i = 0;i < this->rows;i++)
	{
		delete[] data[i];
	}
};

template<typename T>
void TableMatrix<T>::resize(size_t r, size_t c, T value)
{
	for (int i = 0;i < this->rows;i++)
	{
		delete[] data[i];
	}
	data = new T*[r];
	for (int i = 0;i < r;i++)
	{
		data[i] = new T[c];
		std::fill(data[i], data[i] + c, value);
	}
	this->rows = r;
	this->columns = c;
}

template<typename T>
T* TableMatrix<T>::operator[](size_t n)
{
	return data[n];
}

template<typename T>
T& TableMatrix<T>::Get(size_t n, size_t m) const
{
	if ((n < this->rows) || (m < this->columns))
	{
		return data[n][m];
	}
	else
	{
		throw std::out_of_range("indexes are out of range");
	}
}

template<typename T>
void TableMatrix<T>::diag(size_t n, T value)
{
	resize(n, n,T(0));
	int t = 0;
	for (int i = 0;i < n;i++)
	{
		data[i][t] = value;
		t++;
	}

}
template<typename T>
TableMatrix<T>& TableMatrix<T>::operator+=(const TableMatrix<T> other)
{
	if (this->rows != other.rows || this->columns != other.columns)
	{
		throw std::logic_error("sizes of matrixes are not equal");
	}
	else
	{
		for (int i = 0;i < this->rows;i++)
		{
			for (int j = 0;j < this->columns;j++)
			{
				data[i][j] += other.Get(i, j);
			}
		}
		return *this;
	}
}

template<typename T>
TableMatrix<T>& TableMatrix<T>::operator-=(const TableMatrix<T> other)
{
	if (this->rows != other.rows || this->columns != other.columns)
	{
		throw std::logic_error("sizes of matrixes are not equal");
	}
	else
	{
		for (int i = 0;i < this->rows;i++)
		{
			for (int j = 0;j < this->columns;j++)
			{
				data[i][j] -= other.Get(i, j);
			}
		}
		return *this;
	}
}

template<typename T>
TableMatrix<T>& TableMatrix<T>::operator*=(const TableMatrix<T> other)
{
	if (other.rows != this->columns)
	{
		throw std::logic_error("sizes of matrixes are not equal");
	}
	else
	{
		T** c = new T*[this->rows];
		for (int i = 0;i < other.columns;i++)
		{
			c[i] = new T[other.columns];
			std::fill(c[i],c[i]+other.columns,T(0));
		}
		for (int i = 0;i < this->rows;i++)
		{
			for (int j = 0;j < other.columns;j++)
			{
				for (int k = 0;k < this->columns;k++)
				{
					c[i][j] += data[i][k] * other.data[j][k];
				}
			}
		}
		for (int i = 0;i < this->rows;i++)
		{
			delete[] data[i];
		}
		data = c;
		this->columns = other.columns;
		return *this;
	}
}

template<typename T>
TableMatrix<T> TableMatrix<T>::operator+(const TableMatrix<T> other) const
{
	return TableMatrix<T>(*this) += other;
}

template<typename T>
TableMatrix<T> TableMatrix<T>::operator-(const TableMatrix<T> other) const
{
	return TableMatrix<T>(*this) -= other;
}

template<typename T>
TableMatrix<T> TableMatrix<T>::operator*(const TableMatrix<T> other) const
{
	return TableMatrix<T>(*this) *= other;
}

template<typename T>
TableMatrix<T>& TableMatrix<T>::operator+=(T other)
{
	if (this->is_square())
	{
		TableMatrix<T> tmp(this->rows);
		tmp.diag(tmp.get_rows(),other);
		return *this += tmp;
	}
	else
	{
		throw std::logic_error("matrix sholud be squre to do this operation");
	}

}

template<typename T>
TableMatrix<T>& TableMatrix<T>::operator-=(T other)
{
	if (this->is_square())
	{
		TableMatrix<T> tmp(this->rows);
		tmp.diag(tmp.get_rows(),other);
		return *this -= tmp;
	}
	else
	{
		throw std::logic_error("matrix sholud be squre to do this operation");
	}

}

template<typename T>
TableMatrix<T>& TableMatrix<T>::operator*=(T other)
{
	if (this->is_square())
	{
		TableMatrix<T> tmp(this->rows);
		tmp.diag(tmp.get_rows(),other);
		return *this *= tmp;
	}
	else
	{
		throw std::logic_error("matrix sholud be squre to do this operation");
	}

}

template<typename T>
TableMatrix<T> TableMatrix<T>::operator+(T other) const
{
	return TableMatrix<T>(*this) += other;
}

template<typename T>
TableMatrix<T> TableMatrix<T>::operator-(T other) const
{
	return TableMatrix<T>(*this) -= other;
}

template<typename T>
TableMatrix<T> TableMatrix<T>::operator*(T other) const
{
	return TableMatrix<T>(*this) *= other;
}

template<typename T>
bool TableMatrix<T>::operator==(const TableMatrix<T>& other) const
{
    if (this->rows!=other.rows || this->columns!=other.columns)
    {
        return false;
    }
    for (int i=0;i<this->rows;i++)
    {
        if (!std::equal(data[i],data[i]+this->columns,other.data[i],other.data[i]+other.columns))
        {
            return false;
        }
    }
    return true;
}

template<typename T>
bool TableMatrix<T>::operator!=(const TableMatrix<T>& other) const
{
    return !(*this==other);
}
template<typename T>
TableMatrix<T>& TableMatrix<T>::operator=(const TableMatrix<T>& other)
{

    resize(other.rows,other.columns,T(0));
    for (int i=0;i<other.rows;i++)
    {
        std::copy(other.data[i],other.data[i]+other.columns,data[i]);
    }
    return *this;
}
