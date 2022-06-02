#pragma once
#include <vector>
class Stack{
    public:
    Stack() = default; 
    Stack(const Stack& other);
    ~Stack() {clear_up();};
    //методы
    void Push(int a);
    void Pop();
    std::size_t Size(){return size;};
    bool Empty(){return (size == 0);};
    int Get();
    void clear_up();
    //операторы
    bool operator==(const Stack& other);
    bool operator!=(const Stack& other);
    Stack operator=(const Stack& rhs);

    private:
        std::vector<int> arr;
        std::size_t size = 0;

};