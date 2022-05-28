#include "DynamicArray.h"
#include <cstring>
#include <algorithm>

DynamicArray::DynamicArray():
    size(0),
    capacity(0),
    data(nullptr)
{}

DynamicArray::DynamicArray(const DynamicArray& other):
    size(other.size),
    capacity(other.capacity) {
    data = new int[capacity];

    for (int i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

DynamicArray::DynamicArray(const std::initializer_list<int>& lst)
    : size(lst.size())
    , capacity(lst.size())
    , data(nullptr) {
        data = new int[size];
        std::copy(lst.begin(), lst.end(), data);
}

DynamicArray::DynamicArray(size_t sz, const int& x) {
    size = sz;
    capacity = sz;
    data = new int[sz];
    std::fill(data, data + sz, x);
}


DynamicArray::~DynamicArray() {
    delete [] data;
    //std::cout << "Me done!" << std::endl;
}


void DynamicArray::view() {
    int* p;
    p = this->data;
    std::cout << "size : " << this->size << "\n";
    std::cout << "capacity : " << this->capacity << "\n";
    for (int i = 0; i < this->size; ++i) {
        std::cout << *p << " ";
        p++;
    }

}

void DynamicArray::Push_back(const int& value) {
    if (size == capacity) { //написать relocate
        int* newdata;
        newdata = new int[(this->size) * 2];

        //memcpy(this->data, newdata, this->size);
        for (int i = 0; i < size; ++i) { //copy
            newdata[i] = data[i];
        }

        delete[](data);
        data = newdata;
        this->capacity *= 2;
    }

    data[size] = value;
    size++;
}

void DynamicArray::Clear() {
    for (int i = 0; i < size; ++i) {
        data[i] = 0;
    }
    size = 0;
}

size_t DynamicArray::Size() const {
    return size;

}

size_t DynamicArray::Capacity() const {
    return capacity;
}

bool DynamicArray::Empty() const {
    if (capacity == 0) {
        return true;
    }

    return false;
}

int& DynamicArray::operator[](size_t i) const {
    if(i >= this->size) {
        throw std::invalid_argument("Incorrect index");
    }
    return *(data + i);
}

int& DynamicArray::at(size_t i) const {
    if (i >= Size()) {
        throw ("std::out_of_range");
    }
    return *data;
}

void DynamicArray::Pop_back() {
    if (size == 0) {
        throw std::invalid_argument("you cannot delete an element from an empty array");
    } else {
        size--;
    }
}

int* DynamicArray::begin() const {
    return data;
}

int* DynamicArray::end() const {
    return data + size;
}

void DynamicArray::Erase(size_t index) {
    if (size == 0) {
        throw std::invalid_argument("you cannot delete an element from an empty array");
    }
    if (index >= size || index < 0) {
        throw std::invalid_argument("Incorrect index");
    }
    for (int i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }

    size--;
}

void DynamicArray::Resize(size_t newsize) {
    if(newsize < capacity){
        size = newsize;
    }
    else{

        int* newdata;
        newdata = new int[(this->size) * 2];
        //memcpy(this->data, newdata, this->size);
        for (int i = 0; i < size; ++i) { //copy
            newdata[i] = data[i];
        }
        delete[](data);
        data = newdata;
        this->capacity += newsize + 1;
        this->capacity *= 2;
        size = newsize;
    }
}

void DynamicArray::Swap(DynamicArray& other) {
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(data, other.data);
}

int& DynamicArray::At(int i) const {
    if (i < 0 || i >= size) {
        throw std::length_error("Index is out of range");
    }

    return *(data + i);
}

void DynamicArray::Insert(int index, int value) {

    Resize(size + 1);

    if (index < 0 || index >= size || size + 1 >= capacity) {
        throw std::length_error("Index is out of range");
    }


    for (int i = size - 1; i > index; --i) {
        data[i] = data[i - 1];
    }

    data[index] = value;
}

void DynamicArray::Assign(int new_size, int value) {
    Resize(new_size);
    size = new_size;
    std::fill(data, data + size, value);
}

bool DynamicArray::operator== (const DynamicArray& other) const{
    if (size == other.size){
        for (int i = 0; i < size; ++i) {
            if (other.data[i] != data[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

void DynamicArray::operator=(const DynamicArray& other) {
    Resize(other.size);
    std::cout << capacity << " \n ";

    capacity = other.capacity;
    std::copy(other.data, other.data + other.size, data);
}
