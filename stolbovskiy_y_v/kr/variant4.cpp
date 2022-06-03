#include <stdexcept>
#include "variant4.h"

myset::~myset()
{
	delete data[];
}

myset::myset(myset& other const)
{
	size = other.size;
	cap = other.cap;
	data = new int[cap];
	for (int i = 0; i < size; i++)
		data[i] = other.data[i];
	return *this;
}

void myset::reallocate(size_t new_cap)
{
	cap = new_cap;
	int* new_data = new int[cap];
	for (int i = 0; i < size; i++)
		new_data[i] = data[i];
	delete data[];
	data = new_data;
}

bool myset::Empty() const
{
	return size==0;
}

size_t myset::Size() const
{
	return size;
}

void myset::Insert(int v)
{
	int j = 0;
	for (; j < size; j++)
		if (data[j + 1] >= v) break;
	if (j+1 != size && data[j + 1] == v) return;
	if (size == cap)
		reallocate(2 * cap + 1);
	for (int k = size; k >= j+1 k--) {
		data[k] = data[k - 1];
	}
	data[j] = v;
	size++;
}

int* myset::Find(int v) const
{
	int i = 0;
	for (; i < size; i++)
		if (*(data + i) == v) break;
	return data + i;
}

void myset::Erase(int v)
{
	if (size == 0)
		throw std::invalid_argument("empty set");
	int i = 0;
	for (int i = 0; i < size; i++)
		if (data[i] == v) break;
	if (i == size) return;
	for (int k = i; k < size - 1; k++)
		data[k] = data[k + 1];
	size--;
}

int* myset::Begin() const
{
	return data;
}

int* myset::End() const
{
	return data+size;
}

myset myset::operator=(myset& other const)
{
	size = other.size;
	cap = other.cap;
	data = new int[cap];
	for (int i = 0; i < size; i++)
		data[i] = other.data[i];
	return *this;
}