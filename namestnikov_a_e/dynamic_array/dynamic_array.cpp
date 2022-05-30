#include "dynamic_array.h"
#include <stdexcept>

DynamicArray::DynamicArray(std::size_t siize, int value){
    size = siize;
    capacity = siize;
    data = new int[siize];
    std::fill(begin(), end(), value);
}
DynamicArray::DynamicArray(const DynamicArray& other) {
    size = other.size;
    capacity = other.capacity;
    data = new int[capacity];
    std::copy(other.begin(), other.end(), begin());
}
DynamicArray::DynamicArray(const std::initializer_list<int>& list) {
    size = list.size();
    capacity = size;
    data = new int[capacity];
    std::copy(list.begin(), list.end(), data);
}
DynamicArray::~DynamicArray(){
    delete[] data;
}

std::size_t DynamicArray::Size() const {return size;}
std::size_t DynamicArray::Capacity() const {return capacity;}
bool DynamicArray::Empty() const {return size == 0;}

int& DynamicArray::operator[](std::size_t i) const {return data[i];}
int& DynamicArray::at(std::size_t i) const {
    if (i >= Size()) {
        throw std::invalid_argument("Index must be lower than size of array");
    } else {
        return *(data + i);
    }
}

void DynamicArray::push_back(int value){
    if (size == capacity)
    {
        int* new_data = new int[capacity*2];
        std::copy(begin(),end(),new_data);
        delete[] data;
        data = new_data;
        capacity *= 2;
    }
    data[size++] = value;
}
void DynamicArray::pop_back() {
    if (size == 0)
    {
        throw std::invalid_argument("There is nothing to pop");
    }
    else
    {
        size--;
    }
}
void DynamicArray::clear() { size = 0;}
void DynamicArray::erase(std::size_t index) {
    if (index > size)
    {
        throw std::invalid_argument("Index out of range");
    }
    else
    {
        for (int i = index; i < size-1; i++)
        {
            data[i] = data[i+1];
        }
        size--;
    }
}
void DynamicArray::insert(std::size_t index, int value) {
    if (index > size)
    {
        throw std::invalid_argument("Index out of range");
    }
    else
    {
        if (capacity == size)
        {
            int* new_data = new int[capacity*2];
            std::copy(begin(),end(),new_data);
            delete[] data;
            data = new_data;
            capacity *= 2;
        }
        for (int i = size; i>index; i--)
        {
            data[i+1] = data[i];
        }
        data[index] = value;
        size += 1;
    }
}
void DynamicArray::resize(std::size_t new_size) {
    if (new_size < size)
    {
        size = new_size;
    }
    else if (new_size < capacity && new_size > size)
    {
        std::fill(data+size, data+new_size, 0);
        size = new_size;
    } else
    {
        int new_capacity = new_size * 2;
        int* new_data = new int[new_capacity];
        std::copy(begin(), end(), new_data);
        std::fill(new_data + size, new_data + new_size, 0);
        delete[] data;
        data = new_data;
        size = new_size;
        capacity = new_capacity;
    }
}
void DynamicArray::assign(std::size_t new_size, int value) {
    if (capacity > new_size)
    {
        size = new_size;
        std::fill(begin(), end(), value);
    }
    else
    {
        delete[] data;
        size = new_size;
        capacity = size * 2;
        data = new int[capacity];
        std::fill(begin(), end(), value);
    }
}

int* DynamicArray::begin() const {return data;}
int* DynamicArray::end() const {return data+size;}

void DynamicArray::swap(DynamicArray &other) {
    std::swap(data, other.data);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
}

bool DynamicArray::operator==(const DynamicArray &other) const {
    return (size == other.size && std::equal(begin(), end(), other.begin(), other.end()));
}
bool DynamicArray::operator!=(const DynamicArray &other) const {
    return !(*this == other);
}

DynamicArray& DynamicArray::operator=(const DynamicArray &other) {
    if ( capacity > other.capacity)
    {
        size = other.size;std::copy(other.begin(), other.end(),data);
    } else
    {
        delete[] data;
        data = new int[other.capacity];
        size = other.size;
        capacity = other.capacity;
        std::copy(other.begin(), other.end(), data);
    }
    return *this;
}