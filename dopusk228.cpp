#include <iostream>
#include <vector>
#include <initializer_list>
#include <stdexcept>

using namespace std;

class Hyst
{
public:
        Hyst()=default;
        Hyst(initializer_list<double> list);
        Hyst(double value, int64_t length);
        ~Hyst();
        void push_back(double value);
        void vychest(double value,int64_t i);
        void dobavit(double value,int64_t i);
        double Get(int64_t i);
        double Mediana() const;
        int Size() const;
        void Gyst();
        bool operator==(const Hyst& other) const;
        bool operator!=(const Hyst& other) const;
        operator+(const Hyst& other);
        operator-(const Hyst& other);
        operator* (double n);

private:
    int64_t size = 0;
    std::vector<double> data;
};
Hyst::Hyst(double value, int64_t length)
{
    size=length;
    for (int i=0;i<size;i++)
    {
        data.push_back(value);
    }
}
Hyst::~Hyst()
{
    for (int i=0;i<size;i++)
    {
        data.clear();
    }
}
void Hyst::push_back(double value)
{
    data.push_back(value);
    size++;
}
void Hyst::vychest(double value,int64_t i)
{
    data[i]=data[i]-value;
}
void Hyst::dobavit(double value,int64_t i)
{
    data[i]=data[i]+value;
}
double Hyst::Get(int64_t i)
{
    if (size==0)
    {
        throw std::length_error("NO");
    }
    return data[i];
}
double Hyst::Mediana() const
{
    double m;
    for (int64_t i=0;i<size;i++)
    {
        m+=data[i];
    }
    return (m/size);
}
void Hyst::Gyst()
{
    if (size==0)
    {
        throw std::length_error("NO");
    }
    for (int i=0;i<size;i++)
    {
        std::cout<<"value["<<i<<"]="<<data[i]<<endl;
    }
}
bool Hyst::operator==(const Hyst& other) const
{
    return data==other.data;
}
bool Hyst::operator!=(const Hyst& other) const
{
    return data!=other.data;
}
int Hyst::Size() const
{
    return size;
}
int main()
{
    Hyst a(5,2);
    Hyst b(5,3);
    cout<<a.Mediana();

}


