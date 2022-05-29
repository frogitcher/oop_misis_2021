#pragma once 

#include "doctest.h"

#include <initializer_list>
#include <algorithm>
#include <stdexcept>

class dynamic_array
{
public:
    dynamic_array();
    dynamic_array(int size, int value = 0);
    dynamic_array(const dynamic_array& other);
    dynamic_array(const std::initializer_list<int>& input_list);
    ~dynamic_array();

    size_t Size() const;
    size_t Capacity() const;
    bool empty() const;

    bool operator==(const dynamic_array& other) const;
    bool operator!=(const dynamic_array& other) const;
    dynamic_array& operator=(const dynamic_array& other);
    int& operator[](size_t value) const;

    int& at(int value) const;

    void Push_back(int value);
    void Pop_back();
    void Clear();
    void Erase(size_t index);
    void Resize(size_t new_size, int value = 0);
    void insert(size_t index, int value = 0);
    void swap(dynamic_array& other);

    int* begin();
    int* end();
private:
    void Realloc(size_t new_size);
    size_t size = 0;
    size_t capacity = 0;
    int* data = nullptr;
};

