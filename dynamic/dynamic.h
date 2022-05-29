#pragma once
#include <initializer_list>

class dynamic {
private:
    size_t Size = 0;
    size_t Capacity = 0;
    _int64* data;
public:
    dynamic(size_t length);
    dynamic(size_t length, _int64 value);
    dynamic(const std::initializer_list<_int64>& list);
    dynamic(const dynamic& other);
    ~dynamic();

    size_t size() const;
    size_t capacity() const;

    bool empty() const;
    void push_back(_int64 value);
    void pop_back();
    void clear();
    void erase(unsigned _int64 pos);
    void erase(_int64* pos);
    void resize(unsigned _int64 new_size);
    void assign(unsigned _int64 new_size, _int64 value);
    void insert(unsigned _int64 pos, _int64 value);
    void insert(_int64* pos, _int64 value);
    void swap(dynamic& other);

    _int64* begin();
    _int64* end();

    _int64& at(unsigned _int64 pos) const;
    _int64& operator[](unsigned _int64 pos) const;

    dynamic& operator=(const dynamic& rhs);

    bool operator==(const dynamic& rhs) const;
    bool operator!=(const dynamic& rhs) const;
};