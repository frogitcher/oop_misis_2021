#pragma once
#include <initializer_list>
#include <stdexcept>

class DynamicArray {
    public:
    DynamicArray() = default;
    DynamicArray(int64_t size, int value);
    DynamicArray(DynamicArray& other);
   // DynamicArray(std::initializer_list<int> &list);
    ~DynamicArray();
    int& operator[](int64_t i);
    bool Empty() const;
    int Size() const;
    void Insert(int64_t index, int value);
    void Erase(int64_t index);
    int* Begin() const;
    int* End() const;
    void Resize(int64_t new_size); 

    DynamicArray& operator=(DynamicArray& other);

    private:
    int64_t size = 0;
    int64_t capacity = 0;
    int* data = 0;

};

class Set{
    public:

    Set() = default;
    Set(Set& other);
    ~Set() = default;

    void Sort();
    int Size();
    void Insert(int64_t index, int value);


    private:
    DynamicArray a;
};