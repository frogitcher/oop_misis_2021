#pragma once
#include <cstdint>
#include <initializer_list>
#include <memory>
#include "dynamic_array.h"
namespace Tripolsky_D_A {

    template <typename T>
    class DynamicArray;

    template <typename T>  
    class DynamicArrayIterator {
    public:
        DynamicArrayIterator(T*** pointer, const ptrdiff_t id = 0);
        DynamicArrayIterator(const DynamicArrayIterator<T> &other);
        ~DynamicArrayIterator() = default;
        T& operator*();
        ptrdiff_t operator-(const DynamicArrayIterator<T> &other) const;
        DynamicArrayIterator<T>  operator= (const DynamicArrayIterator<T> &other);
        DynamicArrayIterator<T>  operator+ (ptrdiff_t delta) const;
        DynamicArrayIterator<T>  operator+=(ptrdiff_t delta);
        DynamicArrayIterator<T>  operator- (ptrdiff_t delta) const;
        DynamicArrayIterator<T>  operator-=(ptrdiff_t delta);
        DynamicArrayIterator<T>  operator++();
        DynamicArrayIterator<T>  operator++(int);
        DynamicArrayIterator<T>  operator--();
        DynamicArrayIterator<T>  operator--(int);
        bool operator< (const DynamicArrayIterator<T> &rhs);
        bool operator<=(const DynamicArrayIterator<T> &rhs);
        bool operator> (const DynamicArrayIterator<T> &rhs);
        bool operator>=(const DynamicArrayIterator<T> &rhs);
        bool operator==(const DynamicArrayIterator<T> &other);
        bool operator!=(const DynamicArrayIterator<T> &other);
    private:
        T*** ptr = nullptr;
        ptrdiff_t i = 0;
    };

    // implementation
    template <typename T>
    DynamicArrayIterator<T>::DynamicArrayIterator(T*** pointer, const ptrdiff_t id) {
        ptr = pointer;
        i = id;
    }
    template <typename T>
    DynamicArrayIterator<T>::DynamicArrayIterator(const DynamicArrayIterator<T> &other){
        ptr = other.ptr;
        i = other.i;
    }
    template <typename T>
    DynamicArrayIterator<T> DynamicArrayIterator<T>::operator=(const DynamicArrayIterator<T> &other) {
        ptr = other.ptr;
        i = other.i;
        return *this;
    }
    template <typename T>
    T& DynamicArrayIterator<T>::operator*() {
        return **((*ptr)+i);
    }
    template <typename T>
    ptrdiff_t DynamicArrayIterator<T>::operator-(const DynamicArrayIterator<T> &other) const {
        return i - other.i;
    }
    template <typename T>
    DynamicArrayIterator<T> DynamicArrayIterator<T>::operator+=(ptrdiff_t delta) {
        i+=delta;
        return *this;
    }
    template <typename T>
    DynamicArrayIterator<T> DynamicArrayIterator<T>::operator+(ptrdiff_t delta) const {
        DynamicArrayIterator<T> other = *this;
        other+=delta;
        return other;
    }
    template <typename T>
    DynamicArrayIterator<T> DynamicArrayIterator<T>::operator++() {
        ++i;
        return *this;
    }
    template <typename T>
    DynamicArrayIterator<T> DynamicArrayIterator<T>::operator++(int) {
        DynamicArrayIterator<T> old = *this;
        operator++();
        return old;
    }
    template <typename T>
    DynamicArrayIterator<T> DynamicArrayIterator<T>::operator-=(ptrdiff_t delta) {
        i-=delta;
        return *this;
    }
    template <typename T>
    DynamicArrayIterator<T> DynamicArrayIterator<T>::operator-(ptrdiff_t delta) const {
        DynamicArrayIterator<T> other = *this;
        other-=delta;
        return other;
    }
    template <typename T>
    DynamicArrayIterator<T> DynamicArrayIterator<T>::operator--() {
        --i;
        return *this;
    }
    template <typename T>
    DynamicArrayIterator<T> DynamicArrayIterator<T>::operator--(int) {
        DynamicArrayIterator<T> old = *this;
        operator--();
        return old;
    }
    template <typename T>
    bool DynamicArrayIterator<T>::operator< (const DynamicArrayIterator<T> &rhs) {
        return i < rhs.i;
    }
    template <typename T>
    bool DynamicArrayIterator<T>::operator<=(const DynamicArrayIterator<T> &rhs) {
        return i <= rhs.i;
    }
    template <typename T>
    bool DynamicArrayIterator<T>::operator> (const DynamicArrayIterator<T> &rhs) {
        return i > rhs.i;
    }
    template <typename T>
    bool DynamicArrayIterator<T>::operator>=(const DynamicArrayIterator<T> &rhs) {
        return i >= rhs.i;
    }
    template <typename T>
    bool DynamicArrayIterator<T>::operator==(const DynamicArrayIterator<T> &other) {
        return (ptr==other.ptr)&&(i == other.i);
    }
    template <typename T>
    bool DynamicArrayIterator<T>::operator!=(const DynamicArrayIterator<T> &other) {
        return (ptr!=other.ptr)||(i != other.i);
    }
}
