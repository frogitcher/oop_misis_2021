#include <iostream>
#include <vector>
#include <algorithm>
//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

template <typename T>
class hist{
private:
    std::vector<T>key;
    std::vector<double>value;
    size_t size = 0;
public:
    hist() = default;
    size_t Size();
    void push(T k, double val);
    std::vector<T> keys();
    std::vector<double> values();
    double operator [](T k);
    void print();
    void plus(T k, double v);
    void minus(T k, double v);
    double median();
    void sort_key();
    void sort_value();
    double sred_arifm();
    ~hist(){
        key.clear();
        value.clear();
    };
};
template<typename T>
size_t hist<T>::Size(){
    return size;
}

template<typename T>
void hist<T>::plus(T k, double v){
        for(int i=0;i<size;i++){
            if(key[i] == k)value[i] += v;
        }
    }

template<typename T>
double hist<T>::sred_arifm(){
        double res;
        for(int i=0;i<size;i++){
            res += value[i];
        }
        return (res/size);
    }

template <typename T>
void hist<T>::sort_value(){
        for(int i=0;i<size;i++){
            for(int j=0;j<size-1;j++){
                if(value[j] > value[j+1]){
                    std::swap(key[j], key[j+1]);
                    std::swap(value[j], value[j+1]);
                }
            }
        }
    }

template <typename T>
void hist<T>::sort_key(){
        for(int i=0;i<size;i++){
            for(int j=0;j<size-1;j++){
                if(key[j] > key[j+1]){
                    std::swap(key[j], key[j+1]);
                    std::swap(value[j], value[j+1]);
                }
            }
        }
    }

template<typename T>
double hist<T>::median(){
        std::vector<double>r = value;
        std::sort(r.begin(),r.end());
        return(r[size/2]);
    }

template<typename T>
void hist<T>::minus(T k, double v){
        for(int i=0;i<size;i++){
            if(key[i] == k)value[i] -= v;
        }
    }

template<typename T>
void hist<T>::print(){
        for(int i=0;i<size;i++){
            std::cout << key[i] << " " << value[i] << "\n";
        }
    }

template<typename T>
double hist<T>::operator [](T k){
        for(int i=0;i<size;i++){
            if(key[i] == k)return value[i];
        }
    }
template<typename T>
std::vector<T> hist<T>::keys(){
        return key;
    }

template<typename T>
void hist<T>::push(T k, double val){
        for(int i=0;i<size;i++)
            if(key[i] == k)return;
        key.push_back(k);
        value.push_back(val);
        size++;
        return;
    }

template<typename T>
std::vector<double> hist<T>::values(){
    return value;
}
int main(){
    hist<int>h;
    h.push(1,3);
    h.push(2,2);
    h.push(0,1);
    h.print();
    std::cout << "\n";
    h.sort_key();
    h.print();
    std::cout << "\n";
    h.sort_value();
    h.print();
    std::cout << h.sred_arifm() <<"\n";
    for(int i:h.keys())std::cout << i << " ";
    std::cout << "\n";
    for(double i:h.values())std::cout << i << " ";
    std::cout << "\n" << h.Size();
}
