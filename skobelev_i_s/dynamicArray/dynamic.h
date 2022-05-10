#pragma once
#include <initializer_list>
#include <cstdint>

class DynamicArray {
public:
    ~DynamicArray();

    DynamicArray(size_t length = 0, int value = 0);
    DynamicArray(DynamicArray& other);

    DynamicArray(const std::initializer_list<int>& list);

    size_t Size() const;
    size_t Capacity() const;
    bool Empty() const;
    
    int& operator[](size_t i) const;
    int& at(size_t i) const;

    void Push_back(int value);
    void Pop_back();
    void Clear();
    void Erase(size_t index);
    void Resize(size_t newSize);
    void Assign(size_t newSize, int value);
    void Insert(size_t index, int value);

    int* begin();
    int* end();

    void Swap(DynamicArray& other);

    bool operator==(const DynamicArray& other) const;
    bool operator!=(const DynamicArray& other) const;

    DynamicArray& operator=(const DynamicArray& other);

private:
    size_t capacity = 0;
    size_t size = 0;
    int* data;
};