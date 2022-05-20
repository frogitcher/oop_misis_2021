#pragma once

#include <algorithm>
#include <initializer_list>
#include <cstdint>

class DynamicArray {
public:
    DynamicArray() = default;
    DynamicArray(int64_t size, int value);
    DynamicArray(const DynamicArray &other);
    DynamicArray(const std::initializer_list<int> &list);
    ~DynamicArray();

    int64_t getSize() const;
    int64_t getCapacity() const;
    int *getData() const;
    bool empty() const;

    void push_back(int value);
    void pop_back(); // throw if empty
    void clear();
    void erase(int64_t index);
    void resize(int64_t new_size);
    void assign(int64_t new_size, int value);
    void insert(int64_t index, int value);
    void swap(DynamicArray &other);

    int *begin() const;
    int *end() const;

    int &at(int64_t i) const;


    int &operator[](int64_t i) const;
    DynamicArray &operator=(const DynamicArray &rhs);
    bool operator==(const DynamicArray &rhs) const;
    bool operator!=(const DynamicArray &rhs) const;

private:
    int64_t size = 0;
    int64_t capacity = 0;
    int *data = nullptr;
    void change_array(int *new_data, int64_t new_size);
};