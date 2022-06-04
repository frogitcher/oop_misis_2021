#pragma once
#include <initializer_list>
#include <stddef.h>

class DynamicArray {
public:
    DynamicArray() = default;
    DynamicArray(size_t _size, int value=0);
    DynamicArray(const DynamicArray& other);
    DynamicArray(const std::initializer_list<int>& list);
    ~DynamicArray();

    size_t Size() const;
    size_t Capacity() const;
    bool Empty() const;

    int& operator[](const size_t i);
    int& at(size_t i) const;

    void push_back(int _value);
    void pop_back();
    void clear();
    void erase(size_t index);
    void insert(size_t index, int value);
    void resize(size_t new_size);
    void assign(size_t new_size, int value);

    int* begin() const;
    int* end() const;

    void swap(DynamicArray& other);

    bool operator==(const DynamicArray& other) const;
    bool operator!=(const DynamicArray& other) const;
    DynamicArray& operator=(const DynamicArray& other);
private:
    size_t capacity = 0;
    size_t size = 0;
    int* data = new int[0];
};
