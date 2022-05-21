#include <iostream>
#include "stack.h"
#include <stdexcept>

st::st(int new_size) : data(new int[new_size]), sz(new_size), capacity(new_size)
{
}

st::~st()
{
	delete[] data;
}



void st::Push(int value)
{
	if (sz + 1 > capacity)
	{
		reallocate();
	}
	*(data + sz) = value;
	sz++;
}

int st::Pop(int value)
{
	if (sz == 0)
	{
		throw std::invalid_argument("empty");
	}
	int buf = *(data + (sz - 1));
	sz--;
	return buf;
}

size_t st::getsize() const
{
	return sz;
}

int st::Get() const
{
	return *(data + sz - 1);
}

int* st::begin()
{
	return data;
}

int* st::end()
{
	return data + sz;
}

bool st::operator==(const st& other) const
{
	if (sz == other.sz)
	{
		for (size_t i = 0; i < sz; i++)
		{
			if (*(data + i) != *(other.data + i)) return false;
			
		}
		return true;
	}
	return false;
}

bool st::operator!=(const st& other) const
{
	return !(*this == other);
}

st& st::operator=(const st& other)
{
	if (sz < other.sz)
	{
		reallocate(other.sz);
	}
	sz = other.sz;
	std::copy(begin(), end(), other.data);
	return *this;

}




bool st::Empty()
{
	return bool(sz);
}

void st::reallocate(int new_size)
{
	if (new_size == 0)
	{
		capacity += capacity + 1;
		int* new_data = new int[capacity];
		std::copy(begin(), end(), new_data);
		delete[] data;
		data = new_data;
	}
	else
	{
		capacity = new_size;
		int* new_data = new int[capacity];
		std::copy(begin(), end(), new_data);
		delete[] data;
		data = new_data;
	}
}
