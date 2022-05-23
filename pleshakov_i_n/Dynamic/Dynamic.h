#pragma once
#include <cstdint>
#include <initializer_list>

class DynamicArray{
    // Класс динамических массивов

public:
    DynamicArray();
    DynamicArray(size_t length, int value = 0);
    DynamicArray(const DynamicArray& other);
    DynamicArray(const std::initializer_list<int>& input_list);
    ~DynamicArray();

    size_t Size() const;
    size_t Capacity() const;
    bool Empty() const;

    int& operator[](size_t i);
    bool operator==(const DynamicArray& other) const;
    void operator=(const DynamicArray& other);

    int& At(size_t i) const;

    void Push_back(int value);
    void Pop_back();
    void Clear();
    void Resize(size_t new_size);
    void Erase(size_t index);
    void Insert(size_t index, int value);
    void Swap(DynamicArray& other);
    void Assign(size_t new_size, int value);
    int* end();
    int* begin();

private:
    void create_data(size_t new_size);
    size_t array_size = 0;
    size_t array_capacity = 0;
    int* data;
};
