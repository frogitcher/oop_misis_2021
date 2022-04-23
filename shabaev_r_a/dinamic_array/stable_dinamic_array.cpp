//
// Created by 11_11 on 09.04.2022.
//

#include "stable_dinamic_array.h"

Stable_Dynamic_Array::Stable_Dynamic_Array(size_t size, int value):capacity(size) {
    data = new Node*[capacity+1];
    (*data)=new Node;
    (*data)->up=data;
    std::fill_n(std::back_inserter(*this), size, value);

}

Stable_Dynamic_Array::Stable_Dynamic_Array(const Stable_Dynamic_Array &other):capacity(other.size) {
    data = new Node*[capacity+1];
    (*data)=new Node;
    (*data)->up=data;
    std::copy(other.begin(), other.end(), std::back_inserter(*this));
}

Stable_Dynamic_Array::Stable_Dynamic_Array(const std::initializer_list<int> &list):capacity(list.size()) {
    data = new Node*[capacity+1];
    (*data)=new Node;
    (*data)->up=data;
    std::copy((list.begin()), (list.end()), std::back_inserter(*this));
}

size_t Stable_Dynamic_Array::Size() const {
    return size;
}

size_t Stable_Dynamic_Array::Capacity() const {
    return capacity;
}

bool Stable_Dynamic_Array::Empty() const {
    return (size==0);
}

void Stable_Dynamic_Array::push_back(int value) {
    relocate(size + 1);
    size++;
    (*(data+size))=new Node;
    (*(data+size))->up=(data+size);
    (*this)[size-1] = value;



}

void Stable_Dynamic_Array::pop_back() {
    if(size==0) return;
    size--;

}

void Stable_Dynamic_Array::clear() {
    size=0;
}

void Stable_Dynamic_Array::erase(size_t index) {
    while(index!=size-1){
        std::swap((*(data+index))->value, (*(data+index+1))->value);
        index++;
    }
    size--;
}

void Stable_Dynamic_Array::resize(size_t new_size, int value) {
    relocate(new_size);
    while(size!=new_size){
        push_back(value);
    }
}

void Stable_Dynamic_Array::insert(size_t index, int value) {
    if(index>size || index<0){throw std::out_of_range("out of range");}
    while(index<size){
        std::swap((*(data+index))->value, value);
        index++;
    }
    push_back(value);
}

void Stable_Dynamic_Array::swap(Stable_Dynamic_Array &other) {
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(data, other.data);
}

Stable_Dynamic_Array::Stable_Dynamic_Array(Stable_Dynamic_Array &&other) {
    this->swap(other);
}

Stable_Dynamic_Array::iter Stable_Dynamic_Array::begin() {
    return {*data};
}

Stable_Dynamic_Array::iter Stable_Dynamic_Array::end() {

    return {*(data+size)};
}

Stable_Dynamic_Array::const_reference &Stable_Dynamic_Array::operator[](size_t i) const {
    return (*(data+i))->value;
}

Stable_Dynamic_Array::const_reference &Stable_Dynamic_Array::at(size_t i) const {
    if(i>=size){
        throw std::out_of_range("out of range");
    }
    return (*this)[i];
}

Stable_Dynamic_Array &Stable_Dynamic_Array::operator=(const Stable_Dynamic_Array &rhs) {
    auto it=rhs;
    this->swap(it);
    return *this;
}

bool Stable_Dynamic_Array::operator==(const Stable_Dynamic_Array &rhs) const {

    if(rhs.Size()!=size) return false;

    return  std::equal(begin(), end(), rhs.begin(), rhs.end());
}

bool Stable_Dynamic_Array::operator!=(const Stable_Dynamic_Array &rhs) const {
    return !(*this==rhs);
}

void Stable_Dynamic_Array::relocate(size_t new_size) {
    if (new_size <= capacity) return;
    capacity=new_size*2;
    Node** new_data= new Node*[capacity+1];
    for(int i=0; i<size+1; i++){
        *(new_data+i)= new Node;
        *(new_data+i)=*(data+i);
        (*(new_data+i))->up=(new_data+i);
    }
    std::swap(data, new_data);
    delete []new_data;

}

Stable_Dynamic_Array::~Stable_Dynamic_Array() {

    for(size_t i=0; i<size+1; i++){
        delete *(data+i);
    }
    delete []data;

}

Stable_Dynamic_Array::const_iter Stable_Dynamic_Array::begin() const {
    return {*data};
}

Stable_Dynamic_Array::const_iter Stable_Dynamic_Array::end() const {
    return {*(data+size)};
}

int &Stable_Dynamic_Array::operator[](size_t i) {
    return (*(data+i))->value;
}

int &Stable_Dynamic_Array::at(size_t i) {
    if(i>=size){
        throw std::out_of_range("out of range");
    }
    return (*this)[i];
}


Node::Node() {
    value=0;
    up = nullptr;
}


