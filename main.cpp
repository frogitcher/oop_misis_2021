#include <iostream>
#include <string>


class Deck
{
public:
    Deck() = default;
    Deck(std::string& a);

    Deck(const Deck& other);
    Deck(const std::initializer_list<std::string> &list);

    ~Deck()
    {
        delete[] data;
    }
    void Push(const std::string& a);
    void Pop(const std::string& a);
    int64_t Size() const;
    bool Empty() const;
    std::string& Get() const;
    operator==(const Deck& other) const;
    operator!=(const Deck& other) const;
    operator=(const Deck& other);

private:
    std::string* data;
    int64_t size = 0;
};
Deck::Deck(std::string& a)
{
    size++;
    *data=a;
}
Deck::Deck(const Deck& other)
{
    int64_t _size=other.size;
    std::string* _data=other.data;
}

Deck::Deck(const std::initializer_list<std::string> &list)
{
    size=list.size();
    std::copy(list.begin(),list.end(),data);
}

void Deck::Push(const std::string& a)
{
    ++size;
    *(data+size-1)=a;
}
int64_t Deck::Size() const
{
    return size;
}
bool Deck::Empty() const
{
    return (size==0);
}
std::string& Deck::Get() const
{
    return *(data+size-1);
}
Deck::operator==(const Deck& other) const
{
    std::string* _data=other.data;
    int64_t _size = other.size;
    if (other.size!=size)
    {
        return false;
    }
    for (int64_t i=0;i<size;i++)
    {
        if (*(data+i)!=*(_data+i))
        {
            return false;
        }
    }
    return true;
}
/*Deck::operator=(const Deck& other)
{
    size=other.size;
    std::copy(*(other.data),*(other.data+other.size-1),data);
}*/

int main()
{
    return 0;
}


