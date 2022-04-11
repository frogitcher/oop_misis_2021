//
// Created by 11_11 on 09.04.2022.
//

#include "stable_dinamic_array.h"

Iterator_Stable_Dynamic_Array Iterator_Stable_Dynamic_Array::operator+(int a) const {

    Iterator_Stable_Dynamic_Array it=*this;
    it.pos = *((pos->up)+a);
    return it;
}

Iterator_Stable_Dynamic_Array Iterator_Stable_Dynamic_Array::operator+=(int a) {

    pos=*(pos->up+a);
    return *this;
}

Iterator_Stable_Dynamic_Array Iterator_Stable_Dynamic_Array::operator-(int a) const {
    Iterator_Stable_Dynamic_Array it=*this;
    it.pos = *((pos->up)-a);
    return it;
}

Iterator_Stable_Dynamic_Array Iterator_Stable_Dynamic_Array::operator-=(int a) {
    this->pos=*((pos->up)-a);
    return *this;
}

Iterator_Stable_Dynamic_Array Iterator_Stable_Dynamic_Array::operator++() {
    return *this+=1;
}

Iterator_Stable_Dynamic_Array Iterator_Stable_Dynamic_Array::operator++(int a) {
    auto it=*this;
    ++(*this);
    return it;
}

int Iterator_Stable_Dynamic_Array::operator*() const {
    return pos->value;
}

Iterator_Stable_Dynamic_Array::Iterator_Stable_Dynamic_Array(Node *_pos) :pos(_pos){}


Iterator_Stable_Dynamic_Array Iterator_Stable_Dynamic_Array::operator--() {
    return *this-=1;
}

Iterator_Stable_Dynamic_Array Iterator_Stable_Dynamic_Array::operator--(int a) {
    auto it=*this;
    --(*this);
    return it;
}

bool Iterator_Stable_Dynamic_Array::operator==(const Iterator_Stable_Dynamic_Array &other) {
    return this->pos ==other.pos;;
}


Stable_Dynamic_Array::Stable_Dynamic_Array(size_t size, int value):size(size), capacity(size) {
    data = new Node*[capacity+1];
    for(int i=0; i<size; i++){
        (*(data+i))=new Node;
        (*(data+i))->value=value;
        (*(data+i))->up=(data+i);
    }

}

Stable_Dynamic_Array::Stable_Dynamic_Array(const Stable_Dynamic_Array &other):size(other.size), capacity(other.size) {
    data =new Node*[capacity+1];
    for (int i = 0; i < size; ++i) {
        (*(data+i))=new Node;
        (*(data+i))->up=(data+i);
        (*(data+i))->value=(*(other.data+i))->value;
    }
}

Stable_Dynamic_Array::Stable_Dynamic_Array(const std::initializer_list<int> &list):size(list.size()), capacity(list.size()) {
    data =new Node*[capacity+1];
    for (int i = 0; i < size; ++i) {
        *(data+i)=new Node;
        (*(data+i))->up=(data+i);
        (*(data+i))->value=*(list.begin()+i);
    }
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
    if (size + 1 > capacity) relocate(size + 1);
    size++;
    (*(data+size-1))=new Node;
    (*(data+size-1))->value=value;
    (*(data+size-1))->up=(data+size-1);


}

void Stable_Dynamic_Array::pop_back() {
    if(size==0){return;}
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
    if(new_size>capacity) relocate(new_size);
    while(size!=new_size){
        push_back(value);
    }
}

void Stable_Dynamic_Array::insert(size_t index, int value) {
    if(index>size){return;}
    while(index<size){
        std::swap((*(data+index-1))->value, value);
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

Iterator_Stable_Dynamic_Array Stable_Dynamic_Array::begin() {
    return Iterator_Stable_Dynamic_Array(*data);
}

Iterator_Stable_Dynamic_Array Stable_Dynamic_Array::end() {
    if(*(data+size)== nullptr){
        *(data+size)= new Node;
        (*(data+size))->value=0;
        (*(data+size))->up=(data+size);
    }
    return {*(data+size)};
}

int &Stable_Dynamic_Array::operator[](size_t i) const {
    return (*(data+i))->value;
}

int &Stable_Dynamic_Array::at(size_t i) const {
    if(i>=size){
        throw std::out_of_range("size>i");
    }
    return (*this)[i];
}

Stable_Dynamic_Array &Stable_Dynamic_Array::operator=(const Stable_Dynamic_Array &rhs) {
    auto it=rhs;
    this->swap(it);
    return *this;
}

bool Stable_Dynamic_Array::operator==(const Stable_Dynamic_Array &rhs) const {
    for(int i=0; i<size; i++){
        if(data+i != rhs.data+i) return false;
    }
    return true;
}

bool Stable_Dynamic_Array::operator!=(const Stable_Dynamic_Array &rhs) const {
    return !(*this==rhs);
}

void Stable_Dynamic_Array::relocate(int new_size) {
    capacity=new_size*2;
    Node** new_data= new Node*[capacity+1];
    for(int i=0; i<capacity+1; i++){
        *(new_data+i)= nullptr;
    }
    for(int i=0; i<size; i++){
        *(new_data+i)=*(data+i);
        (*(new_data+i))->up=(new_data+i);
    }
    std::swap(data, new_data);
    delete []new_data;

}

Stable_Dynamic_Array::~Stable_Dynamic_Array() {
    delete []data;
}


Node::Node() {
    value=0;
    up = nullptr;
}


