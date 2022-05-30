#pragma once
#include <memory>
#include <initializer_list>

class DynamicArray{
public:
    DynamicArray() = default;
    DynamicArray(std::size_t length, int value = 0);
    DynamicArray(const DynamicArray& other);
    DynamicArray(const std::initializer_list<int>& list);
    ~DynamicArray();

    std::size_t Size() const;
    std::size_t Capacity() const;
    bool Empty() const;

    int& operator[](std::size_t i) const;
    int& at(std::size_t i) const;

    void push_back(int value);
    void pop_back(); //throw exception
    void clear();
    void erase(std::size_t index);
    void insert(std::size_t index, int value);
    void resize(std::size_t new_size);
    void assign(std::size_t new_size, int value);

    int* begin() const;
    int* end() const;

    void swap(DynamicArray& other);

    bool operator==(const DynamicArray& other) const;
    bool operator!=(const DynamicArray& other) const;

    DynamicArray& operator=(const DynamicArray& other);

private:
    std::size_t capacity = 0;
    std::size_t size = 0;
    int* data;
};