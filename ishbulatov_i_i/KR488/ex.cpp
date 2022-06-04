#include <stdexcept>
#include <initializer_list>
#include "ex.h"

gistogram::gistogram(int64_t _size, int64_t _cap,int value):size(_size),cap(_cap){
    data=new int[_cap];
    std::fill(data,data+size,value);
}
gistogram::gistogram(const gistogram &other):size(other.size),cap(other.size){
    data=new int [other.size];
    std::copy(data,data+size,other.data);
}
gistogram::~gistogram(){
    delete [] data;
}
&gistogram::operator [](int _key){
    return *(data[_key]);
}
gistogram::operator+(int x,int _key){
    data[_key]+=x;
}
gistogram::operator-(int x, int _key){
    data[_key]-=x;
}
gistogram::void print(int _size){
    for (_size=0;_size<size;_size++){
        cout <<"key "<<_size<<"- "<<data[_size];
    }
}
