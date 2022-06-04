#include <utility>
#include <vector>
#include "algorithm"
#include <iostream>

template <typename T>
class Hist{
public:
    Hist() = default;
    Hist(std::vector<T> _keys, std::vector<double> _values){
        keys = _keys;
        values = _values;
    }

    Hist(Hist const &hist){
        keys = hist.keys;
        values = hist.values;
    }


    void append(T key, double value){
        if (!check_in(key)){
            keys.push_back(key);
            values.push_back(value);
        }
    }

    void del(T key){
        for (int i = 0; i < keys.size(); ++i){
            if (keys[i] == key){
                keys.erase(keys.begin() + i);
                values.erase(values.begin() + i);
            }
        }
    }

    size_t get_size() const{
        return keys.size();
    }

    double mean() const{
        double s = 0;
        for (int i = 0; i < keys.size(); ++i){
            s += values[i];
        }
        return s / keys.size();
    }

    double median() const{
        std::vector<double> copy_values = values;
        sort(copy_values.begin(), copy_values.end());
        return copy_values[copy_values.size() / 2];
    }

    double get(T key) const{
        for (int i = 0; i < keys.size(); ++i){
            if (keys[i] == key){
                return values[i];
            }
        }
        return  0.0;
    }

    void add(T key, double x){
        for (int i = 0; i < keys.size(); ++i){
            if (keys[i] == key){
                values[i] += x;
            }
        }
    }

    void substract(T key, double x){
        for (int i = 0; i < keys.size(); ++i){
            if (keys[i] == key){
                values[i] -= x;
            }
        }
    }

    void multiply(T key, double x){
        for (int i = 0; i < keys.size(); ++i){
            if (keys[i] == key){
                values[i] *= x;
            }
        }
    }

    void divide(T key, double x){
        for (int i = 0; i < keys.size(); ++i){
            if (keys[i] == key){
                values[i] /= x;
            }
        }
    }

    double operator[](T key) const{
        for (int i = 0; i < keys.size(); ++i){
            if (keys[i] == key){
                return values[i];
            }
        }
        return  0.0;
    }

    Hist<T> operator=(Hist<T> hist){
        return Hist(hist);
    }

    void print() const{
        for (int i = 0; i < keys.size(); ++i){
            std::cout << keys[i] << " " << values[i] << "\n";
        }
    }


private:
    std::vector<T> keys;
    std::vector<double> values;

    bool check_in(T value){
        for (int i = 0; i < keys.size(); ++i){
            if (keys[i] == value) {
                return true;
            }
        }
        return false;
    }
};
