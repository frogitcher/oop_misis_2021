#pragma once
#include <cstdint>
#include <initializer_list>

class DynamicArray
{
private:
    int64_t capacity=0;
    int64_t size=0;
    int* data;
public:
    DynamicArray()=default;
    DynamicArray(int64_t length,int value=0);
    DynamicArray(const DynamicArray& other);
    DynamicArray(const std::initializer_list<int> list);
    ~DynamicArray();

    int64_t Size();
    int64_t Capacity();
    bool Empty() const;
    int& operator[] (int64_t i) const;
    int& at(int64_t i) const;
    void push_back(int value);
    void pop_back ();
    void clear();
    void erase(int64_t index);
    void insert(int64_t index, int value);
    void resize(int64_t new_size);
    void reallocate(int64_t _capacity);
    void resize(int64_t new_size,int value);
    void assign(int64_t _size, int value);
    void swap(DynamicArray& other);
    int* begin();
    int* end();
    bool operator==(const DynamicArray& other) const;
    bool operator!=(const DynamicArray& other) const;
    DynamicArray& operator=(const DynamicArray& other);
};
