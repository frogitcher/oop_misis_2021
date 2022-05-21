#include <initializer_list>
#include <iostream>
#include <vector>
class Vector
{
private:
    std::vector<double> data;

public:
    Vector(std::vector<double> &values);
    Vector(std::initializer_list<double> list);
    ~Vector() = default;

    // double operator[];
    Vector *operator=(Vector &other);
    bool operator==(Vector &other) const;
    bool operator!=(Vector &other) const;
    Vector *operator+(Vector &other);
    Vector *operator-(Vector &other);
    double operator*(Vector &other);
    Vector *operator*=(double &value); // умножение на число
};

Vector::Vector(std::vector<double> &values)
{
    this->data = values;
}

Vector::Vector(std::initializer_list<double> list)
{
    data = std::vector<double>(list.size(), 0.0);
    for (int i = 0; i < list.size(); i++)
    {
        data[i] = double(list.begin() + i);
    }
}

Vector *Vector::operator=(Vector &other)
{
    this->data = other.data;
    return this;
}

bool Vector::operator==(Vector &other) const
{
    if (this->data.size() != other.data.size())
    {
        return false;
    }
    return this->data == other.data;
}

bool Vector::operator!=(Vector &other) const
{
    return !(*this == other);
}

Vector *Vector::operator+(Vector &other)
{
    if (this->data.size() != other.data.size())
    {
        return this; // return exeption;
    }
    for (int i = 0; i < data.size(); i++)
    {
        this->data[i] += other.data[i];
    }
    return this;
}

Vector *Vector::operator-(Vector &other)
{
    if (this->data.size() != other.data.size())
    {
        return this; // return exeption;
    }
    for (int i = 0; i < data.size(); i++)
    {
        this->data[i] += other.data[i];
    }
    return this;
}

Vector *Vector::operator*=(double &value)
{

    for (int i = 0; i < this->data.size(); ++i)
    {
        this->data[i] *= value;
    }
    return this;
}

double Vector::operator*(Vector &other)
{
    double result = 0.0;
    if (this->data.size() != other.data.size())
    {
        return 0.0; // return exeption;
    }
    for (int i = 0; i < this->data.size(); ++i)
    {
        result += this->data[i] * other.data[i];
    }
    return result;
}

int main()
{
    return 0;
}