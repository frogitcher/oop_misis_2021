#ifndef DYNAMICARRAY_DYNAMIC_ARRAY_H
#define DYNAMICARRAY_DYNAMIC_ARRAY_H

#pragma once
#include <memory>
#include<initializer_list>

using namespace std;

// ~~sorry~~
class DynamicArray {
public:

    DynamicArray();

    DynamicArray(const size_t size, const int value);

    DynamicArray(const DynamicArray &copy);

    DynamicArray(const initializer_list<int> &list);

    ~DynamicArray();

    /*
     * Operators
     * */
    int &operator[](const size_t index) const;

    DynamicArray &operator=(const DynamicArray &rhs);

    bool operator==(const DynamicArray &rhs) const;

    bool operator!=(const DynamicArray &rhs) const;


    /*
     * Main Methods
     * */

    // Resizes the container to contain count elements
    void resize(const size_t newSize);

    // value --- the value to initialize the new elements with
    void resize(const size_t newSize, const int &value);

    // Inserts an element in index+1 position
    void insert(const size_t index, const int &value);

    // Removes an element from index+1 position
    void erase(const size_t index);

    // Adds a new element at the end
    void push_back(const int &value);

    // Removes the last element
    void pop_back();

    // Replaces the contents with count copies of value
    void assign(const size_t newSize, const int &value);

    // Replaces the contents with the elements from the initializer list
    void assign(const initializer_list<int> &list);

    // Exchanges the content
    void swap(DynamicArray &copy);

    // Erases all elements from the container (MAKE SIZE = 0)
    void clear();

    // Returns an iterator pointing to the first element
    int *begin() const;

    // Returns an iterator pointing to the last element
    int *end() const;

    // Returns a reference to the element at specified location pos, with bounds checking
    int& at(const size_t index) const;

    // Getters size and capactity
    size_t Size() const;
    size_t Capacity() const;

    // Returns whether the vector is empty
    bool Empty() const;

private:
    std::size_t size;
    std::size_t capacity;
    int *data;

    void reallocate(const std::size_t newSize);
};


#endif //DYNAMICARRAY_DYNAMIC_ARRAY_H
