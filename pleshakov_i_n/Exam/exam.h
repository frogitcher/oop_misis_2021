#include <stdexcept>

template <typename T>
class Set{

public:
    Set() = default;
    Set(const Set<T>& s);
    Set(const std::initializer_list<T>& List);
    ~Set();

    size_t Size() const;
    T* Begin() const;
    T* End() const;
    void Insert(const T& value, const size_t& index);
    void Erase(const T& index);
    bool Empty() const;
    void operator=(const Set<T>& s);
    void Erase(const T& index);
    T* Find(const T& value) const;


private:
    void Relocate(const size_t& value);
    size_t size = 0;
    T* data = nullptr;
};

template <typename T>
void Set<T>::Relocate(const size_t& value){
    T* new_data = new T[value];
    for (int i = 0; i < size; ++i){
        new_data[i] = data[i];
    }
    size = value;
    delete[]data;
    data = new_data;
}

template <typename T>
Set<T>::Set(const Set<T>& s)
    : size(s.size){
        data = new T[size];
        for (int i = 0; i < size; ++i){
            data[i] = s.data[i];
        }
}

template <typename T>
Set<T>::~Set(){
    delete[]data;
    size = 0;
}

template <typename T>
size_t Set<T>::Size() const{
    return size;
}

template <typename T>
T* Set<T>::Begin() const{
    return data;
}

template <typename T>
T* Set<T>::End() const{
    return data + size;
}

template <typename T>
void Set<T>::Insert(const T& value, const size_t& index){
    if (index > size){
        throw std::invalid_argument("Invalid index");
    }else{
        bool flag = true;
        for (int i = 0; i < size; ++i){
            if (data[i] == value){
                flag = false;
                throw std::invalid_argument("value is already in Set");
            }
        }
        if (flag){
            Relocate(size + 1);
            for (int i = size - 1; i > index; --i){
                data[i] = data[i-1];
            }
            data[index] = value;
        }
    }
}

template <typename T>
bool Set<T>::Empty() const{
    return (size == 0);
}

template <typename T>
void Set<T>::operator=(const Set<T>& s){
    size = s.size;
    data = new T[size];
    for (int i = 0; i < size; ++i){
        data[i] = s.data[i];
    }
}

template <typename T>
void Set<T>::Erase(const T& value){
    size_t index;
    bool flag = false;
    for (int i = 0; i < size; ++i){
        if (data[i] == value){
            index = i;
            flag = true;
            break;
        }
    }
    if (flag){
        for (int i = index; i < size - 1; ++i){
            data[i] = data[i + 1];
        }
        --size;
    } else{
        throw std::invalid_argument("invalid argument");
    }
}

template <typename T>
T* Set<T>::Find(const T& value) const{
    for (int i = 0; i < size; ++i){
        if (data[i] == value){
            return data + i;
        }
    }
    return data + size;
}
