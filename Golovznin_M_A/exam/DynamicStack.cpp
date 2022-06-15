#include "DynamicStack.h"

DynamicStack::DynamicStack(int _size, int value) : size(_size) {
    changeCapacity(_size);
    data = new int[capacity];
    std::fill(data, data + size, value);
}

DynamicStack::DynamicStack(DynamicStack &other) : size(other.Size()) {
    changeCapacity(other.Size());
    data = new int[capacity];
    for (int i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

DynamicStack::DynamicStack(std::initializer_list<int> list) {
    size = list.size();
    changeCapacity(size);
    data = new int[capacity];
    std::copy(list.begin(), list.end(), data);

}

DynamicStack::~DynamicStack() {
    delete data;
}

void DynamicStack::Push(int value) {
    if (capacity < size + 1) {
        changeCapacity(size);
        int *newData = new int[capacity];
        std::copy(data, data + size, newData);
        newData[size] = value;
        data = newData;
    } else {
        data[size] = value;
    }
}

int DynamicStack::Pop() {
    int value = data[size - 1];
    data[size - 1] = 0;
    size--;
    return value;
}

int64_t DynamicStack::Size() {
    return size;
}

bool DynamicStack::Empty() {
    return size == 0;
}

int DynamicStack::Get() {
    return data[size - 1];
}

bool DynamicStack::operator==(const DynamicStack &rhs) const {
    if (size != rhs.size) {
        return false;
    }

    for (int i = 0; i < size; ++i) {
        if (data[i] != rhs.data[i]) {
            return false;
        }
    }

    return true;
}

bool DynamicStack::operator!=(DynamicStack &rhs) const {
    return !(*this == rhs);
}

DynamicStack &DynamicStack::operator=(DynamicStack &rhs) {
    DynamicStack ds(rhs);
    *this = ds;
    return *this;

}

void DynamicStack::changeCapacity(int64_t size) {
    while (capacity < size) {
        capacity *= 2;
    }
}
