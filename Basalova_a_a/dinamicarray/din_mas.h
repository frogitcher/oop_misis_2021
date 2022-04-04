#include <iostream>

using namespace std;

class DinamicArray {
private:
    size_t size;// логический размер
    size_t capacity;//реальный размер
    int* data;
public:
    DinamicArray() = default;
    DinamicArray(size_t length, int value = 0):size(length), capacity(length) {
        data = new int[length];
        fill(data, data + length, value);
    };
    DinamicArray(const DinamicArray& obj) {
        data = new int[obj.Size()];
        for (int i = 0; i < obj.Size(); i++) {
            data[i] = obj[i];
        }
    };
    //DinamicArray(const initializer_list<int>& list);
    ~DinamicArray() {
        if(data != NULL)
        delete[] data;
    }

    size_t Size() const {
        return size;
    }
    bool Empty() const {
        return(size == 0);
    }
    int& operator [](size_t i) const{
        return data[i];
    }
    int& at(size_t i)const {
        if (i > Size()) {
            throw; 
        }
        return data[i];
    }
    void push_back(int value) {
        if (size == capacity) {
            if (capacity != 0) {
                int* new_data = new int[capacity * 2];
                copy(data, data + capacity * 2, new_data);
                delete[] data;
                data = new_data;
            }
            capacity *= 2;
            capacity++;
        }
        data[size] = value;
        size++;
    }
    void pop_back() {
        if (size > 0) {
            int* new_data = new int[size-1];
            copy(data, data + size-1, new_data);
            delete[] data;
            data = new_data;
            size -= 1;
            capacity = size;
        }
    }
    void clear() {
        delete[] data;
        data = NULL;
        size = 0;
        capacity = 0;
    }
    void erase(size_t i) {
        for (int k = i + 1; k < size; k++) {
            data[k - 1] = data[k];
        }
        int* new_data = new int[size - 1];
        copy(data, data + size - 1, new_data);
        delete[] data;
        data = new_data;
        size -= 1;
        capacity = size;
    }
    void resize(size_t new_size) {
        if (new_size < size) {
            int* new_data = new int[new_size];
            copy(data, data + new_size, new_data);
            delete[] data;
            data = new_data;
            size = new_size;
            capacity = size;
        }
        else {
            int* new_data = new int[new_size];
            copy(data, data + new_size, new_data);
            delete[] data;
            data = new_data;
            for (int i = size; i < new_size; i++)
                data[i] = 0;
            size = new_size;
            capacity = size;
        }
    }
    
    int* begin() {
        return data;
    }
    int* end() {
        return data + size;
    }
    bool operator ==(const DinamicArray& other)const {
        if (size != other.Size())return false;
        for (int i = 0; i < size; i++)
            if (data[i] != other[i])return false;
        return true;
    }
    void insert(size_t i, int value) {
        if (size == capacity) {
            if (capacity != 0) {
                int* new_data = new int[capacity * 2];
                copy(data, data + capacity * 2, new_data);
                delete[] data;
                data = new_data;
            }
            capacity *= 2;
            capacity++;
        }
        size++;
        capacity = size;
        for (int k = i + 1; k < size; k++)
            data[k] = data[k - 1];
        data[i] = value;
    }
    void assign(size_t new_size, int value) {
        data = new int[new_size];
        fill(data, data + new_size, value);
        size = new_size;
        capacity = size;
        for (int i = 0; i < new_size; i++)data[i] = value;
    }
    // DinamicArray& - возвращам значение по ссылке, чтобы можно было делать цепочку присваиваний
    DinamicArray& operator =(const DinamicArray& other) { // вот здесь поменяла тип результата
        if (this != &other) // чтобы не было присваивания самого себе
        {
            size = other.Size();
            capacity = other.capacity; 
            if (data != NULL)
                delete[] data;
            data = new int[size];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i]; // вот здесь поменяла
            }
        }
        return *this;
    }
    void swap(DinamicArray& other) {
        DinamicArray c;
        c = *this;
        *this = other;
        other = c;
        

    }
};

/*int main()
{
    DinamicArray a(5, 12);
    DinamicArray b;
    b.assign(2, 3);
    a.push_back(5);
    //for (int i = 0; i < a.Size(); i++)cout << a[i] << " ";
    cout << "a: ";
    a.insert(2, 7);
    for (int i = 0; i < a.Size(); i++)cout << a[i] << " ";
    cout << "\n";
    //a.swap(b);
    //for (int i = 0; i < b.Size(); i++)cout << b[i] << " ";
    cout << "b: ";
    for (int i = 0; i < b.Size(); i++)cout << b[i] << " ";
    cout << "\n";
    DinamicArray d;
    d = b = a;
    cout << "b: ";
    for (int i = 0; i < b.Size(); i++)cout << b[i] << " ";
    cout << "\n";
    cout << "d: ";
    for (int i = 0; i < d.Size(); i++)cout << d[i] << " ";
    cout << "\n";
    return 0;
}
*/
