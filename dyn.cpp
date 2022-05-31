#include <stdexcept>
#include <initializer_list>
#include "dyn.h"

DynamicArray::DynamicArray(int64_t length,int value):size(length),cap(length){
    data=new int [length];
    std::fill(data,data+size,value);
}
DynamicArray::DynamicArray(const DynamicArray& other):size(other.size),cap(other.cap){
    int *data=new int[cap];
    std::copy(other.data,data,other.data+size,_data);
    data=_data;
}
DynamicArray::DynamicArray(const std::initializer_list <int> list):size(list.size),cap(list.size){
    data=new int[size];
    std::copy(list.begin(),list.end(),data);
}
DynamicArray::~DynamicArray(){
    delete[] data;
}
int64_t DynamicArray::size(){
    return size;
}
int64_t DynamicArray::cap(){
    return cap;
}
bool DynamicArray::empty() const{
    return (size==0);
}
int& DynamicArray::operator [] (int64_t i) const{
    return *(data+i);
}
int& DynamicArray:: at(int64_t i) const{
    if(i>=size ||i<0){
        throw   std::length_error("index out of range");
    }
    return *(data+i);
}
void DynamicArray::push_back(int value){
    resize(size++);
    data[size-1]=value;
}
void DynamicArray::pop_back(){
    if (size==0){
        throw std::length_error("array is empty");
    }
    size--;
}
void DynamicArray::clear(){
    size=0;
}
void DynamicArray::erase(int64_t index){
    if (index>size || index<0){
        throw std::length_error("index out of range");
    }
    std::copy(data+index+1,data+size,data+index);
    size--;
}
void DynamicArray::insert (int64_t index,int value){
    if(index>size || index<0){
        throw std::length_error("index out of range");
    }
    resize(size++);
    std::copy_backward(begin()+index,end(),data);
    data[index]=value;
}
void DynamicArray::resize (int64_t _size){
    if(_size<0){
        throw std::length_error("size cannot be less than zero");
    }
    if (_size==0){
        size=_size;
        return;
    }
    reallocate(_size);
    if (size<_size){
        std::fill(begin()+size,begin()+_size,0);
    }
    size=_size;
}
void DynamicArray::assign(int64_t _size,int value){
    resize(_size);
    std::fill(begin(),begin()+_size,value);
}
void DynamicArray::reallocate( int64_t _cap){
    if (_cap>cap){
        cap=_cap;
        int *_data=new int[_cap];
        delete[] data;
        data=_data;
    }
}
void DynamicArray::swap(DynamicArray& other){
    std::swap(size,other.size);
    std::swap(cap,other.cap);
    std::swap(data,other.data);
}
int* DynamicArray::begin(){
    return data;
}
int* DynamicArray::end(){
    return data+size;
}
bool DynamicArray::operator ==(const DynamicArray& other) const{
    return (size==other.size)&&std::equal(data,data+size,other.data,other.data+size);
}
bool DynamicArray::operator !=(const DynamicArray& other) const{
    return !(*this==other);
}
DynamicArray& operator =(const DynamicArray& other){
    resize(other.size());
    std::copy(other.begin(),other.end,data);
    return *this;
}
