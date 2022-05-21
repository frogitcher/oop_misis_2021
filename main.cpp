/*
    made by Omar Zoloev
*/

#include <iostream>

class Stack{

private:
    int* data = nullptr;
    int Size = 0;
    int sz = 0;

public:
    Stack(size_t Size_in): Size(Size_in){
        data = new int [Size];
    }
    Stack(const Stack& b){
        this->data = (b.data);
        this->sz = (b.sz);
        this->Size = (b.Size);
    }
    ~Stack(){
        delete[]data;
    }

    void Push(int in){
        if(sz + 1 > Size){
        int* data_new = new int[sz * 2];
            for(int i = 0; i < sz; ++i){
                    data_new[i] = data[i];
            }
            data = new int[sz * 2];
            for(int i = 0; i < sz; ++i){
                    data[i] = data_new[i];
            }
            delete[]data_new;
            data[sz + 1] = in;
            sz++;
        }else{
            sz++;
            data[sz] = in;
        }
    }
    void Get()const{
        if(sz == 0){
            std::cout << "Stack is empty" << "\n";
        }else{

        std::cout << data[sz];
        }

    }
    void Empty()const{
        if(sz == 0){
            std::cout << "Yes";
        }
        else{
            std::cout << "No";
        }
    }
    void Pop(){
        if(sz > 0){
            sz--;
        }
        else{
            std::cout << "Stack is empty" << "\n";
        }
    }
    void Stack_size() const{
        std::cout << sz << "\n";
    }

    bool operator == (const Stack& rhs){
        if(this->sz != rhs.sz){
            return 0;
        }
        int cnt = 0;
        for(int i = 0; i <= sz; ++i){
            if(this->data[i] == rhs.data[i]){
                cnt++;
            }
        }
        if(cnt == sz + 1){
            return 1;
        }else{
            return 0;
        }
    }

    bool operator != (const Stack& rhs){
        if(this->sz != rhs.sz){
            return 1;
        }
        int cnt = 0;
        for(int i = 0; i <= sz; ++i){
            if(this->data[i] == rhs.data[i]){
                cnt++;
            }
        }
        if(cnt == sz + 1){
            return 0;
        }else{
            return 1;
        }
    }



    Stack& operator = (const Stack& rhs){

        this->sz = (rhs.sz);
        this->Size = (rhs.Size);
        //delete[]data;
        this->data = &(rhs.data[0]);

        return *this;
    }


};

int main()
{
    Stack a(5);
    a.Push(5);
    a.Push(655);

    Stack b(5);
    b.Push(5);
    b.Push(67);

    b = a;
    b.Get();



    return 0;
}
