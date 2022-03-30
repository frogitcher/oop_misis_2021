#include "class_dynamic_array.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
Dynamic_array::Dynamic_array(size_t n, int value)
{
	size = n;
	capacity = n*2;
	data = new int[n];
	std:: fill(data,data+size,value);
}

Dynamic_array::Dynamic_array(const Dynamic_array& other)
{
	size = other.size;
	capacity = other.size;
	data = other.data;
}

Dynamic_array::~Dynamic_array() {
	delete[] data;
}
Dynamic_array::Dynamic_array(const std::initializer_list<int>& other)
{
	size = other.size();
	capacity = other.size() * 2;
	data = new int[other.size()*2];
	std::copy(other.begin(),other.end(),data);
}

int& Dynamic_array:: operator[](size_t i)
{
	if (i>size)
    {
        throw std::out_of_range("index out of range");
    }
    else
    {
        return *(data+i);
    }
}

size_t Dynamic_array:: Capacity() const
{
	return capacity;
}

size_t Dynamic_array::Size() const
{
	return size;
}

bool Dynamic_array::Empty() const
{
	if (size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Dynamic_array::push_back(int value)
{
	if (size == capacity && capacity!=0)
	{
		capacity *= 2;
		int* temp_data = new int[capacity];
		std::copy(temp_data, temp_data + size, data);
		delete[] data;
		data = temp_data;
	}
	data[size++] = value;
}

void Dynamic_array::pop_back()
{
	if (size != 0)
	{
		data[--size] = 0;
	}
	else
	{
		throw std::range_error("Dynamic array has no elements!");
	}
}

void Dynamic_array::assign(size_t n, int value)
{
    size=n;
    capacity=n*2;
    data=new int[n*2];
    std::fill(data,data+n,value);
}
void Dynamic_array::clear()
{
    delete[] data;
    size=0;
}

void Dynamic_array::erase(size_t i)
{
    if (i<size)
    {
        for (int j=i;j<size-1;j++)
        {
            data[j]=data[j+1];
        }
        size--;
    }
    else
    {
        throw std::logic_error("impossible to erase element that is out of array range");
    }
}

int* Dynamic_array::begin()
{
    return data;
}

int* Dynamic_array::end()
{
    return data+size;
}

void Dynamic_array::swap(Dynamic_array& other)
{
    std::swap(size,other.size);
    std::swap(capacity,other.capacity);
    std::swap(data,other.data);
}

bool Dynamic_array::operator==(const Dynamic_array& other) const
{
    std::string data1="";
    std::string data2="";
    for (int i=0;i<size;i++)
    {
        data1+=std::to_string(data[i]);
    }
    for (int i=0;i<other.size;i++)
    {
        data2+=std::to_string(other.data[i]);
    }
    return data1==data2;
}

bool Dynamic_array::operator!=(const Dynamic_array& other) const
{
    std::string data1="";
    std::string data2="";
    for (int i=0;i<size;i++)
    {
        data1+=std::to_string(data[i]);
    }
    for (int i=0;i<other.size;i++)
    {
        data2+=std::to_string(other.data[i]);
    }
    return data1!=data2;
}

bool Dynamic_array::operator>=(const Dynamic_array& other) const
{
    std::string data1="";
    std::string data2="";
    for (int i=0;i<size;i++)
    {
        data1+=std::to_string(data[i]);
    }
    for (int i=0;i<other.size;i++)
    {
        data2+=std::to_string(other.data[i]);
    }
    return data1>=data2;
}

bool Dynamic_array::operator<=(const Dynamic_array& other) const
{
    std::string data1="";
    std::string data2="";
    for (int i=0;i<size;i++)
    {
        data1+=std::to_string(data[i]);
    }
    for (int i=0;i<other.size;i++)
    {
        data2+=std::to_string(other.data[i]);
    }
    return data1<=data2;
}

bool Dynamic_array::operator>(const Dynamic_array& other) const
{
    std::string data1="";
    std::string data2="";
    for (int i=0;i<size;i++)
    {
        data1+=std::to_string(data[i]);
    }
    for (int i=0;i<other.size;i++)
    {
        data2+=std::to_string(other.data[i]);
    }
    return data1>data2;
}

bool Dynamic_array::operator<(const Dynamic_array& other) const
{
    std::string data1="";
    std::string data2="";
    for (int i=0;i<size;i++)
    {
        data1+=std::to_string(data[i]);
    }
    for (int i=0;i<other.size;i++)
    {
        data2+=std::to_string(other.data[i]);
    }
    return data1<data2;
}

