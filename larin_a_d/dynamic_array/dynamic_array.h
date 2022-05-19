#pragma once
#include <cstdint>
#include <initializer_list>
#include <algorithm>

class DynamicArray {
    public:
        DynamicArray(int64_t size = 0, int value = 0);
        DynamicArray(const DynamicArray& other);
        DynamicArray(const std::initializer_list<int>& list);
        ~DynamicArray();

        int64_t Size() const;
        int64_t Capacity() const;
        inline bool Empty() const {
            return size == 0;
        }
        inline int* GetData() const {
            return data;
        }

        void push_back(int value);
        void pop_back();
        inline void clear() {
            size = 0;
        }
        void erase(int64_t index);
        void resize(int64_t new_size, int value = 0);
        void assign(int64_t new_size, int value = 0);
        void insert(int64_t index, int value);
        void swap(DynamicArray& other);

        inline int* begin() {
            return data;
        }

        inline int* end() {
            return data + size;
        }

        inline int& operator[](int64_t i) const {
            return *(data + i);
        }
        int& at(int64_t i) const;

        DynamicArray& operator=(const DynamicArray& rhs);

        bool operator==(const DynamicArray& rhs) const {
            return std::equal<int*, int*>(data, data + size, rhs.data);
        }
        inline bool operator!=(const DynamicArray& rhs) const {
            return !(*this == rhs);
        }

        inline friend void Reallocate(DynamicArray& da, int64_t new_size) {
            da.reallocate(new_size);
        }

    private:
        int64_t size = 0;
        int64_t capacity = 0;
        int* data;

        void reallocate(int64_t new_capacity);
};

inline void Reallocate(DynamicArray& da, int64_t new_size);
