#include <iostream>
#include <initializer_list>
#include <algorithm>
class Set
{
public:
    Set()
    {
        data = new int[size];
    }

    Set(const std::initializer_list<int>& list)
    {
        int* temp_data = new int[list.size()];
        for (int i = 0;i < list.size();i++)
        {
            temp_data[i] = -11000;
        }
        int count(0);
        for (int i : list)
        {
            bool in = false;
            for (int j = 0;j < list.size();j++)
            {
                if (temp_data[j] == i)
                {
                    in = true;
                    break;
                }
            }
            if (in == false)
            {
                temp_data[count] = i;
                count++;
            }
        }
        size = count;
        data = new int[size];
        count = 0;
        for (int i = 0;i < list.size();i++)
        {
            if (temp_data[i] != -11000)
            {
                data[count] = temp_data[i];
                count++;
            }
        }
        std::sort(data, data + size);
        delete[] temp_data;
    }

    Set(const Set& other)
    {
        size = other.size;
        data = new int[size];
        std::copy(other.data, other.data + other.size, data);
    }

    ~Set()
    {
        delete[] data;
    }

    bool Empty() const
    {
        if (size == 0)
        {
            return true;
        }
        return false;
    }

    int Size() const
    {
        return size;
    }

    void insert(const int value)
    {
        if (At(value) == false)
        {
            int* temp_data = new int[size + 1];
            for (int i = 0;i < size;i++)
            {
                temp_data[i] = data[i];
            }
            temp_data[size] = value;
            size++;
            std::sort(temp_data, temp_data + size);
            delete[] data;
            data = temp_data;
        }
    }

    bool At(const int value)
    {
        for (int i = 0;i < size;i++)
        {
            if (data[i] == value)
            {
                return true;
            }
        }
        return false;
    }

    int find(const int value) //возвращает позицию или -1 если нету
    {
        if (At(value) == false)
        {
            return (-1);
        }
        for (int i = 0;i < size;i++)
        {
            if (data[i] == value)
            {
                return i;
            }
        }
    }

    int Get(const int i)
    {
        return data[i];
    }

    int erase(const int i)
    {

    }

    int& begin() const
    {
        return *data;
    }

    int& end() const
    {
        return *(data + size);
    }

private:
    int* data;
    size_t size = 0;
};