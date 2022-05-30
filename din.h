#include <iostream>

using namespace std;

class DinamicArray {
private:
    size_t size = 0;
    size_t capacity = 0;
    int* data;

public:

    DinamicArray();
    DinamicArray(size_t n, int val = 0);
    DinamicArray(const DinamicArray& a);
    DinamicArray(const initializer_list<int>& list);

    size_t Size() const;
    bool Empty() const;

    int& operator[](size_t i) const;
    int& At(size_t i)const;

    void Push_back(int value);
    void Pop_back();
    void Clear();
    void Erase(size_t i);
    void Resize(size_t new_size);

    void Insert(size_t i, int value);
    void Assign(size_t new_size, int value);
    void Swap(DinamicArray& a);



    int* begin()const;
    int* end()const;

    bool operator==(const DinamicArray& a);
    bool operator!=(const DinamicArray& a);
    DinamicArray& operator=(const DinamicArray& a);

    ~DynamicArray();
};
