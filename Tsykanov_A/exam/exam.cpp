#include "exam.h"
#include <stdexcept>
#include <iostream>
Stack::Stack(const Stack& other){
    arr = other.arr;
    size = other.size;
};
void Stack::Push(int a){
    arr.push_back(a);
    size += 1;
};
void Stack::Pop(){
    if (size == 0){
        std::cout << "Exeption: Stack is empty";
    }
    else{
        arr.pop_back();
        size -= 1;
    }
}
int Stack::Get(){
    if (size == 0){
        throw std::exception();
    }
    return arr[size];
};
void Stack::clear_up(){
    while(size){
        arr.pop_back();
    }
};
// операторы
bool Stack::operator==(const Stack& other){
    if (size == other.size){
        bool flag = true;
        for(int i = 0; i < size; i++){
            if (arr[i] != other.arr[i]){
                flag = false;
                break;
            }
        }
        if (flag){
            return true;
        }
        else{
            return false;
        }
    }
    return false;
};
bool Stack::operator!=(const Stack& other){
    return !(*this == other);
};
Stack Stack::operator=(const Stack& rhs){
    
};