#ifndef SET_H
#define SET_H

#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

template<class Type>
class Set {
public:
    Set() = default;
    Set(const Set<Type>& copy) = default;
    Set(const std::vector<Type>& copy);
    ~Set() { data_.clear(); }

    Set<Type>& operator=(const Set<Type>& rhs) = default;
    Set<Type>& operator+=(const Type& rhs);
    Set<Type>& operator-=(const Type& rhs);
    Set<Type>& operator-=(const Set<Type>& rhs);
    Set<Type>& operator&=(const Set<Type>& rhs);
    Set<Type>& operator|=(const Set<Type>& rhs);
    Set<Type>& operator^=(const Set<Type>& rhs);

    Set<Type> operator+(const Type& rhs) const;
    Set<Type> operator-(const Type& rhs) const;
    Set<Type> operator-(const Set<Type>& rhs) const;
    Set<Type> operator&(const Set<Type>& rhs) const;
    Set<Type> operator|(const Set<Type>& rhs) const;
    Set<Type> operator^(const Set<Type>& rhs) const;

    bool operator==(const Set<Type>& rhs) const { return this->data_ == rhs.data_; }

    void Insert(Type val) { *this += val; }
    void Erase(Type val) { *this -= val; }

    void Clear() { data_.clear(); }

    bool Empty() const { return data_.size() == 0; }

    int64_t Size() const { return data_.size(); }

    typename std::vector<Type>::iterator Begin() { return data_.begin(); }
    typename std::vector<Type>::iterator End() { return data_.end(); }

    typename std::vector<Type>::iterator Find(Type val);

    std::ostream& Print(std::ostream& ostream) const;

private:
    static const char kOpenBracket{ '{' };
    static const char kCloseBracket{ '}' };
    std::vector<Type> data_;
};

template<class Type>
Set<Type>::Set(const std::vector<Type>& copy) {
    for (auto it : copy) {
        this->Insert(it);
    }
    return;
}

template<class Type>
Set<Type>& Set<Type>::operator+=(const Type& rhs) {
    for (auto it : data_) {
        if (it == rhs) return *this;
    }
    data_.push_back(rhs);
    std::stable_sort(data_.begin(), data_.end());
    return *this;
}

template<class Type>
Set<Type>& Set<Type>::operator-=(const Type& rhs) {
    for (int64_t i = 0; i < data_.size(); ++i) {
        if (data_[i] == rhs) {
            for (int64_t j = i + 1; j < data_.size(); ++j) {
                data_[j - 1] = data_[j];
            }
            data_.resize(data_.size() - 1);
            break;
        }
    }
    return *this;
}

template<class Type>
Set<Type>& Set<Type>::operator-=(const Set<Type>& rhs) {
    for (auto it_rhs : rhs.data_) {
        *this -= it_rhs;
    }
    return *this;
}

template<class Type>
Set<Type>& Set<Type>::operator&=(const Set<Type>& rhs) {
    Set<Type> lhs = *this;
    this->data_.resize(0);
    for (auto it_lhs : lhs.data_) {
        for (auto it_rhs : rhs.data_) {
            if (it_lhs == it_rhs) {
                *this += it_lhs;
                break;
            }
        }
    }
    return *this;
}

template<class Type>
Set<Type>& Set<Type>::operator|=(const Set<Type>& rhs) {
    for (auto it_rhs : rhs.data_) {
        *this += it_rhs;
    }
    return *this;
}

template<class Type>
Set<Type>& Set<Type>::operator^=(const Set<Type>& rhs) {
    *this = (rhs | *this) - (rhs & *this);
    return *this;
}


template<class Type>
Set<Type> Set<Type>::operator+(const Type& rhs) const {
    Set<Type> lhs = *this;
    return lhs += rhs;
}

template<class Type>
Set<Type> Set<Type>::operator-(const Type& rhs) const {
    Set<Type> lhs = *this;
    return lhs -= rhs;
}

template<class Type>
Set<Type> Set<Type>::operator-(const Set<Type>& rhs) const {
    Set<Type> lhs = *this;
    return lhs -= rhs;
}

template<class Type>
Set<Type> Set<Type>::operator&(const Set<Type>& rhs) const {
    Set<Type> lhs = *this;
    return lhs &= rhs;
}

template<class Type>
Set<Type> Set<Type>::operator|(const Set<Type>& rhs) const {
    Set<Type> lhs = *this;
    return lhs |= rhs;
}

template<class Type>
Set<Type> Set<Type>::operator^(const Set<Type>& rhs) const {
    Set<Type> lhs = *this;
    return lhs ^= rhs;
}

template<class Type>
typename std::vector<Type>::iterator Set<Type>::Find(Type val) {
    auto it = data_.begin();
    for (; it != data_.end(); ++it) {
        if (*it == val) break;
    }
    return it;
}

template<class Type>
std::ostream& Set<Type>::Print(std::ostream& ostream) const {
    ostream << kOpenBracket << ' ';
    for (auto it: data_) {
        ostream << it << ' ';
    }
    ostream << kCloseBracket << '\n';
    return ostream;
}

#endif // SET_H
