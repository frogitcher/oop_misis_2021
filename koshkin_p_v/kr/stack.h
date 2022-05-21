#pragma once 

class stack
{
public:
    stack();
    ~stack();

    int Size() const;
    bool Empty() const;
    int Get() const;

    void Push(int value);
    void Pop();
    void Realloc(int value);

    bool operator==(const stack& other) const;
    bool operator!=(const stack& other) const;
    stack& operator=(const stack& other);
    int& operator[](int value) const;
private:
    size_t size = 0;
    size_t capacity = 0;
    int* data = 0;
};

