#pragma once
#include <ostream>
#include <vector>
class gistogram{
private:
    int* data;
    int64_t cap=0;
    int64_t size=0;
public:
    gistogram()=default;
    gistogram(int64_t _size,int64_t _cap,int value);
    gistogram(const gistogram &other);
    ~gistogram();
    &gistogram operator [](int _key);
    gistogram operator+ (int _key,int x);
    gistogram operator- (int _key,int x);
    void print(int index);
};
