#pragma once
#include<initializer_list>
#include <stddef.h>
class DynamicArray {
private:
    size_t capacity = 0;
    size_t size = 0;
    int* data;
    void realloc(size_t new_capacity);
public:
    //DynamicArray() = default;
    DynamicArray(size_t _size = 0, int value = 0);
    DynamicArray(const DynamicArray& other);
    DynamicArray(const std::initializer_list<int>& list);
    ~DynamicArray() = default;
  const  size_t Size() const;
  const size_t Capacity() const;
    bool Empty() const;
    int& operator[](size_t i);
    int& at(size_t i);
    void push_back(int value);
    void pop_back();
    void clear();
    void erase(size_t index);
    void insert(size_t index,int value);
    void assign(size_t new_size, int value);
    int* begin() const;
    int* end() const;
    void swap(DynamicArray& other);
    bool operator==(const DynamicArray& other) const;
    bool operator!=(const DynamicArray& other) const;
    DynamicArray& operator=(const DynamicArray& other);
};
