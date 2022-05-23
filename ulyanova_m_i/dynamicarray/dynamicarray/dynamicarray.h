#pragma once
#include <cstddef>
#include <initializer_list>
#include <cstdint>

class DynamicArray {

public:

    DynamicArray();
    DynamicArray(int64_t Length, int value = 0);
    DynamicArray(const DynamicArray& other);
    DynamicArray(const std::initializer_list<int>& list);
    ~DynamicArray();

    int64_t Size() const;
    int64_t Capacity() const;
    int* GetData();
    bool Empty() const;

    void Push_back(int value);
    void Pop_back(); 
    void Clear();
    void Erase(int64_t index);
    void Resize(int64_t new_size);
    void Swap(DynamicArray& other);
    void Assign(int64_t new_size, int value);
    void Insert(int64_t index, int value);
    
    int* begin();
    int* end();

    bool operator==(const DynamicArray& other); 
    bool operator!=(const DynamicArray& other); 
    DynamicArray& operator=(const DynamicArray& other);

    int& At(int64_t i) const;
    int& operator[](int64_t i) const;

    void Realocate(int64_t new_size);

private:
    int64_t size = 0;
    int64_t capacity = 0;
    int* data;
};