#pragma once
#include <cstdint>
#include <initializer_list>
#include <algorithm>

class DynamicArray {
    public:
        DynamicArray(int64_t size = 0, int value = 0);
        DynamicArray(const DynamicArray& another);
        DynamicArray(const std::initializer_list<int>& list);

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
        void swap(DynamicArray& another);
        void insert(int64_t index, int value);

        inline int* begin() const{
            return data;
        }

        inline int* end() const{
            return data + size;
        }

        inline int& operator[](int64_t i) const {
            return *(data + i);
        }
        int& at(int64_t i) const;

        DynamicArray& operator=(const DynamicArray& rhs);

        bool operator==(const DynamicArray& rhs) const {
            return (size == rhs.size && std::equal<int*, int*>(data, data + size, rhs.data));
        }
        inline bool operator!=(const DynamicArray& rhs) const {
            return !(*this == rhs);
        }

        inline friend void Reallocate(DynamicArray& da, int64_t new_size) {
            da.reallocate(new_size);
        }
        ~DynamicArray();

    private:
        int64_t size = 0;
        int64_t capacity = 0;
        int* data;

        void reallocate(int64_t new_capacity);
};

inline void Reallocate(DynamicArray& da, int64_t new_size);
