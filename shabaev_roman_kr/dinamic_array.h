//
// Created by 11_11 on 21.05.2022.
//

#ifndef PROJECT_DINAMIC_ARRAY_H
#define PROJECT_DINAMIC_ARRAY_H


#include <algorithm>

class dinamic_array {
public:
    dinamic_array();
    dinamic_array(const dinamic_array& other);
    dinamic_array(dinamic_array&& other) noexcept;
    void operator =(const dinamic_array&other);
    void operator =(dinamic_array&&other);

    void push_back( int value);
    void pop_back();
    int back();


private:
    int* data;
    int size, capacity;
    void add_smt(int new_size); //call if you nedd to add smt
    void relocate(int new_size);
};

dinamic_array::dinamic_array(dinamic_array &&other) noexcept {
    data=other.data;
    other.data= nullptr;
}

void dinamic_array::push_back(int value) {
    add_smt(size+1);
    size++;
    *(data+size-1)=value;
}

void dinamic_array::pop_back() {
    --size;
}

int dinamic_array::back() {

    return *(data+size-1);
}

void dinamic_array::relocate(int new_size) {
    auto it=new int[new_size];
    capacity=new_size;
    for(int i=0; i<size; i++){
        *(it+i)=*(data+i);
    }
    std::swap(data, it);
    delete[] it;
}

void dinamic_array::add_smt(int new_size) {
    if(new_size<capacity) return;
    relocate(new_size*2);

}

dinamic_array::dinamic_array(): data(nullptr), size(0), capacity(0){

}

dinamic_array::dinamic_array(const dinamic_array &other):dinamic_array() {
    relocate(other.size);
    size=other.size;
    for(int i=0; i<other.size; i++){
        *(data+i)=*(other.data+i);
    }

}

void dinamic_array::operator=(dinamic_array &&other) {
    data=other.data;
    size=other.size;
    capacity=other.capacity;
}

void dinamic_array::operator=(const dinamic_array &other) {
    relocate(other.size);
    size=other.size;
    for(int i=0; i<size; i++){
        *(data+i)=*(other.data+i);
    }

}


#endif //PROJECT_DINAMIC_ARRAY_H
