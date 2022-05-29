#pragma once
#include <cstddef>
#include <initializer_list>

class DynamicArray {
    public:
        DynamicArray();
        DynamicArray(size_t size, int value = 0);
        DynamicArray(const DynamicArray& other);
        DynamicArray(const std::initializer_list<int>& list);
        ~DynamicArray();

        size_t Size() const;
        size_t Capacity() const;
        bool Empty() const;

        void push_back(int value);
        void pop_back(); 
        void clear();
        void erase(size_t index);
        void resize(size_t new_size, int value = 0 );
        void insert(size_t index, int value);
        void swap(DynamicArray& other);

        int* begin();
        int* end();

        int& At(size_t i) const;

        int& operator[](size_t i) const;
 
        DynamicArray& operator=(const DynamicArray& rhs);
        bool operator==(const DynamicArray& rhs) const;
        bool operator!=(const DynamicArray& rhs) const;
    private:
  
        //Force resize capacity using new memory allocation
        void remapmemory(size_t new_size);
        size_t _size = 0;
        size_t _capacity = 0;
        int* _data = 0;
};