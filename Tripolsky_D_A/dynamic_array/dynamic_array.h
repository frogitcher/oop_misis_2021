#pragma once
#include <cstdint>
#include <initializer_list>
#include <memory>
#include "dynamic_array_iterator.h"
#include <stdexcept>
namespace Tripolsky_D_A {

    template <typename T>
    class DynamicArrayIterator;

    template <typename T>
    class DynamicArray {
    public:
        typedef DynamicArrayIterator<T> Iterator;
        DynamicArray();
        DynamicArray(const size_t& new_size);
        DynamicArray(const size_t& new_size, const T& value);
        DynamicArray(const DynamicArray <T>& other);
        DynamicArray(const DynamicArrayIterator<T> &other_begin, const DynamicArrayIterator<T> &other_end);
        DynamicArray(const std::initializer_list<T>& list);
        void assign(const size_t& new_size);
        void assign(const size_t& new_size, const T& value);
        void assign(const DynamicArray <T>& other);
        void assign(DynamicArrayIterator<T> other_begin, const DynamicArrayIterator<T>& other_end);
        void assign(const std::initializer_list<T>& list);
        ~DynamicArray();

        size_t size() const;
        size_t capacity() const;
        bool Empty() const;

        void resize(const size_t& new_size);
        void resize(const size_t& new_size, const T& value);
        void clear();

        void push_back(const T& value);
        void pop_back();

        void insert(const size_t& index, const T& value);
        void erase(const size_t& index);

        T& operator[](size_t i);
        T& at(size_t i);
        const T& operator[](size_t i) const;
        const T& at(size_t i) const;
        T& front(); 
        T& back();
        bool operator==(const DynamicArray<T> &other) const;
        bool operator!=(const DynamicArray<T> &other) const;
        
        Iterator begin();
        Iterator end();
    public:
        void reallocate(const size_t& new_size);
        size_t size_ = 0;
        size_t capacity_ = 0;
        T** data = nullptr;
    };

    // implementation

    template <typename T>
    DynamicArray<T>::DynamicArray() {
        size_ = 0; capacity_ = 1;
        data = new T*[capacity_]{nullptr};
    }
    template <typename T>
    DynamicArray<T>::DynamicArray(const size_t& new_size) {
        size_ = 0; capacity_ = 1;
        data = new T*[capacity_]{nullptr};
        *data = new T;
        assign(new_size);
    }
    template <typename T>
    void DynamicArray<T>::assign(const size_t& new_size) {
        resize(new_size);
    }
    template <typename T>
    DynamicArray<T>::DynamicArray(const size_t& new_size, const T& value) {
        size_ = 0; capacity_ = 1;
        data = new T*[capacity_]{nullptr};
        *data = new T;
        assign(new_size,value);
    }
    template <typename T>
    void DynamicArray<T>::assign(const size_t& new_size, const T& value) {
        size_t old_size = size_;
        resize(new_size);
        if (size_ < old_size) old_size = size_;
        for (T** i = data; i < data+old_size; ++i) {
            **i = value;
        }
    }
    template <typename T>
    DynamicArray<T>::DynamicArray(const DynamicArrayIterator<T> &other_begin, const DynamicArrayIterator<T> &other_end) {
        size_ = 0; capacity_ = 1;
        data = new T*[capacity_]{nullptr};
        *data = new T;
        assign(other_begin,other_end);
    }
    template <typename T>
    void DynamicArray<T>::assign(DynamicArrayIterator<T> other_begin, const DynamicArrayIterator<T> &other_end) {
        if (other_begin >= other_end) throw std::out_of_range("out of range");
        resize(other_end - other_begin);
        for (DynamicArray::Iterator begin_ = begin();other_begin<other_end;++begin_,++other_begin) {
            *begin_ = *other_begin;
        }
    }
    template <typename T>
    DynamicArray<T>::DynamicArray(const std::initializer_list<T>& list) {
        size_ = 0; capacity_ = 1;
        data = new T*[capacity_]{nullptr};
        *data = new T;
        assign(list);
    }
    template <typename T>
    void DynamicArray<T>::assign(const std::initializer_list<T>& list) {
        resize(list.size());
        for (size_t i = 0; i < size_; ++i) {
            **(data+i) = *(list.begin()+i);
        }
    }
    template <typename T>
    DynamicArray<T>::DynamicArray(const DynamicArray <T>& other) {
        size_ = 0; capacity_ = 1;
        data = new T*[capacity_]{nullptr};
        *data = new T;
        assign(other);
    }
    template <typename T>
    void DynamicArray<T>::assign(const DynamicArray <T>& other) {
        resize(other.size());
        for (size_t i = 0; i < size_; ++i) {
            *(data+i) = other[i];
        }
    }
    template <typename T>
    DynamicArray<T>::~DynamicArray() {
        for(size_t i = 0; i < size_; ++i) {
            delete *(data+i);
        }
        delete[] data;
    }
    template <typename T>
    void DynamicArray<T>::reallocate(const size_t& new_size){
        if (new_size <= capacity_) return;
        size_t old_capacity = capacity_;
        for ( ; capacity_ < new_size; capacity_<<=1) {}
        T** new_data = new T*[capacity_];
        std::copy(data,data+old_capacity,new_data);
        delete[] data;
        data = new_data;
    }
    template <typename T>
    size_t DynamicArray<T>::size() const { return size_; }
    template <typename T>
    size_t DynamicArray<T>::capacity() const { return capacity_; }
    template <typename T>
    bool DynamicArray<T>::Empty() const { return (size_==0); }
    template <typename T>
    void DynamicArray<T>::resize(const size_t& new_size){
        for (size_t i = new_size; i < size_; ++i) {
            delete *(data+i);
        }
        reallocate(new_size);
        for (size_t i = size_; i < new_size; ++i) {
            *(data+i) = new T;
        }
        size_ = new_size;
    }
    template <typename T>
    void DynamicArray<T>::resize(const size_t& new_size,const T& value){
        for (size_t i = new_size; i < size_; ++i) {
            delete *(data+i);
        }
        reallocate(new_size);
        for (size_t i = size_; i < new_size; ++i) {
            *(data+i) = new T(value);
        }
        size_ = new_size;
    }
    template <typename T>
    void DynamicArray<T>::clear() {
        resize(0);
    }
    template <typename T>
    void DynamicArray<T>::push_back(const T& value) {
        resize(size_+1,value);
    }
    template <typename T>
    void DynamicArray<T>::pop_back() {
        if (size_ > 0) resize(size_ - 1);
    }
    template <typename T>
    T& DynamicArray<T>::operator[](size_t i) {
        if (size_<=i) throw std::out_of_range("out of range");
        return **(data+i);
    }
    template <typename T>
    T& DynamicArray<T>::at(size_t i) {
        if (size_<=i) throw std::out_of_range("out of range");
        return **(data+i);
    }
    template <typename T>
    const T& DynamicArray<T>::operator[](size_t i) const {
        if (size_<=i) throw std::out_of_range("out of range");
        return **(data+i);
    }
    template <typename T>
    const T& DynamicArray<T>::at(size_t i) const {
        if (size_<=i) throw std::out_of_range("out of range");
        return **(data+i);
    }
    template <typename T>
    DynamicArrayIterator<T> DynamicArray<T>::begin() {
        return DynamicArrayIterator<T>(&data);
    }
    template <typename T>
    DynamicArrayIterator<T> DynamicArray<T>::end() {
        return DynamicArrayIterator<T>(&data,size_);
    }
    template <typename T>
    T& DynamicArray<T>::front() {
        return **(data);
    }
    template <typename T>
    T& DynamicArray<T>::back() {
        return **(data+size_);
    }
    template <typename T>
    void DynamicArray<T>::insert(const size_t& index,const T& value) {
        if (size_ < index) throw std::out_of_range("out of range");
        reallocate(size_+1);
        for (size_t i = size_; index < i; --i) {
            *(data+i) = *(data+i-1);
        }
        *(data+index) = new T(value);
        ++size_;
    }
    template <typename T>
    void DynamicArray<T>::erase(const size_t& index) {
        if (size_ <= index) throw std::out_of_range("out of range");
        delete *(data+index);
        for (size_t i = index; i < size_; ++i) {
            *(data+i) = *(data+i+1);
        }
        --size_;
        *data(size_) = nullptr;
    }
    template <typename T>
    bool DynamicArray<T>::operator!=(const DynamicArray<T>& rhs) const {
        if (size_!=rhs.size_) return true;
        for (size_t i = 0; i < size_; ++i)
            if (at(i) != rhs[i])
                return true;
        return false;
    }
    template <typename T>
    bool DynamicArray<T>::operator==(const DynamicArray<T>& rhs) const {
        if (size_!=rhs.size_) return false;
        for (size_t i = 0; i < size_; ++i)
            if ((**(data+i)) !=rhs[i])
                return false;
        return true;
    }


}
