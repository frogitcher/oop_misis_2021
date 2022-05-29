#pragma once
#include <ostream>

//сложно писать не подсматривая в синтаксис, извиняюсь, если это очень плохо написано(
class Stack_kr {
public:
    Stack_kr() = default;
    ~Stack_kr() {
        delete[] data;
    }
    Stack_kr(const std::initializer_list()& lists) {
        stack_size = lists.size();
        data = new int* data_stack;
        for(int i = 0; i < stack_size; i++) {
            data.push_back(lists[i]);
        };
    };
    Stack_kr(const Stack_kr& other) {
        size_stack = other.size_stack;
        data = new int* data_stack;
        for (int i = 0; i < size_stack; i++) {
            data.push_back(other.data[i]);
        };
    };
    void Push (const int a) {
        data.push_back(a);
    };
    void Pop() {
        data.pop_back(a); //еще надо выдать ощибку если стек пуст
    };
    int Size() const {
        return data.size_stack();
    };
    bool operator==(const Stack_kr& other) const {
        flag = true;
        if (this->size_stack == other.size_stack) {
            for ( int i = 0; i < this->size_stack; i++) {
                if ( this->data[i]!=data[i] ) {
                    flag = false;
                }
            }
        }
        else {
            flag = false;
            return flag;
        };

        return flag;
    };
    bool operator!=(const Stack_kr& other) const {
        return !(Stack_kr == other.Stack_kr);
    };
    int Get() {
        if(size_stack > 0) {
            return data[-1];
        };
        //тут тоже выкинуть ошибку если размер меньше 0
    };
    bool Empty() {
        if (size_stack == 0) {
            return true:
        }
        else {
            return false;
        };
    };
    Stack_kr operator=(const Stack_kr& other) {
        size_stack = other.size_stack;
        data = new int* data_stack;
        for (int i = 0; i < size_stack; i++) {
            data.push_back(other.data[i]);
        };
    };
private:
    int size_stack;
    *int data;
};
