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

    int& operator[](int i);
    bool operator==(const DynamicArray& other) const;
    void operator=(const DynamicArray& other);

    int& at(int i) const;

    void push_back(int value);
    void pop_back();
    void clear();
    int* end();
    void resize(size_t new_size);
    void erase(size_t index);
    void insert(size_t index, int value);
    int* begin();
    void swap(DynamicArray& other);
    void assign(size_t new_size, int value);

private:
    void create_data(size_t new_size);
    size_t array_size = 0;
    size_t array_capacity = 0;
    int* data;
};
