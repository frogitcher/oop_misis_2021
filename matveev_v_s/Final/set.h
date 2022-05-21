#define SET

#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

template <class Type>
class Set
{x`x``
public:
    Set() = default;
    Set(const Set<Type> &copy) = default;
    Set(const std::vector<Type> &copy);
    ~Set() { data_.clear(); }

    Set<Type> &operator=(const Set<Type> &rhs) = default;
    Set<Type> &operator+=(const Type &rhs);
    Set<Type> &operator-=(const Type &rhs);
    Set<Type> &operator-=(const Set<Type> &rhs);
    Set<Type> &operator&=(const Set<Type> &rhs);
    Set<Type> &operator|=(const Set<Type> &rhs);
    Set<Type> &operator^=(const Set<Type> &rhs);

    Set<Type> operator+(const Type &rhs) const;
    Set<Type> operator-(const Type &rhs) const;
    Set<Type> operator-(const Set<Type> &rhs) const;
    Set<Type> operator&(const Set<Type> &rhs) const;
    Set<Type> operator|(const Set<Type> &rhs) const;
    Set<Type> operator^(const Set<Type> &rhs) const;
}