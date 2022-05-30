#pragma once

#include <cstdint>
#include <initializer_list>
#include <stddef.h>

class DynamicArray {
public:
    DynamicArray() = default;

    DynamicArray(size_t _size, int fill_value = 0);

    DynamicArray(const DynamicArray &dyn_array);

    DynamicArray(const std::initializer_list<int> &init_list);

    ~DynamicArray();

    size_t Size() const;

    size_t Capacity() const;

    bool Empty() const;

    int &operator[](const size_t index);

    int &at(size_t i) const;

    void push_back(int push_value);

    void pop_back();

    void clear();

    void erase(size_t index);

    void insert(size_t index, int insert_value);

    void resize(size_t new_size);

    void assign(size_t new_size, int value);

    int *begin() const;

    int *end() const;

    void swap(DynamicArray &swap_value);

    bool operator==(const DynamicArray &other_dyn_array) const;

    bool operator!=(const DynamicArray &other_dyn_array) const;

    DynamicArray &operator=(const DynamicArray &other_dyn_array);

private:
    size_t capacity = 0;
    size_t size = 0;
    int *data = new int[0];
};