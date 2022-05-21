#include <vector.h>
#include <math.h>
#include <stdexcept>

vector::~vector()
{
	delete[] data;
}

vector::vector(int size)
{
	size = size;
	*double data = new data[size];
	std::fil(data, data + size, 0);
}

vector vector::operator=(const vector& other)
{
	delete[] data;
	size = other.Size();
	*double data = new data[size];
	std::fil(data, data + size, other.data);
	return *this;
}

vector::vector(vector& other const)
{
	delete[] data;
	size = other.Size();
	*double data = new data[size];
	std::fil(data, data + size, other.data);
}

double vector::operator[](int i)
{
	return *(data + i);
}
double vector::at(int i)
{
	if (i >= size / 2 || i < 0)
		throw sdt::out_of_range ""
	return *(data + i);
}
int vector::Size()
{
	return size;
}

bool vector::operator==(const vector& other)
{
	if (size != other.Size())
		return false;
	for (int i = 0; i < size; i++)
	{
		if (*(data + i) != *(other.data + i))
			return false;
	}
	return true;
}

bool vector::operator!=(const vector& other)
{
	return !(*this == other);
}

double vector::norm()
{
	double ans = 0;
	for(i = 0; i < size; i++)
	{
		ans += *(data + i) * *(data + i);
	}
	ans = std::sqrt(ans);
	return ans;
}

vector vector::operator*(const vector& other) const
{
	vector(size) a;
	for (int i = 0; i < size; i++)
	{
		*(a.data + i) = *(data + i) * *(other.data + i);
	}
	return a;
}

vector vector::operator+(const vector& other) const
{
	vector(size) a;
	for (int i = 0; i < size; i++)
	{
		*(a.data + i) = *(data + i) + *(other.data + i);
	}
	return a;
}

vector vector::operator-(const vector& other) const
{
	vector(size) a;
	for (int i = 0; i < size; i++)
	{
		*(a.data + i) = *(data + i) - *(other.data + i);
	}
	return a;
}

vector vector::operator*(double scale) const
{
	vector(size) a;
	for (int i = 0; i < size; i++)
	{
		*(a.data + i) = *(data + i) * scale;
	}
	return a;
}


void vector::operator+=(const vector& other)
{
	for (int i = 0; i < size; i++)
	{
		*(data + i) = *(data + i) + *(other.data + i);
	}
}
void vector::operator-=(const vector& other)
{
	for (int i = 0; i < size; i++)
	{
		*(data + i) = *(data + i) - *(other.data + i);
	}
}
void vector::operator*=(const vector& other)
{
	for (int i = 0; i < size; i++)
	{
		*(data + i) = *(data + i) * *(other.data + i);
	}
}
void vector::operator*=(double scale)
{
	for (int i = 0; i < size; i++)
	{
		*(data + i) = *(data + i) * scale;
	}
}