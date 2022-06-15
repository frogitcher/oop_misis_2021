#include <initializer_list>
#include <algorithm>
#include <cstdint>

class DynamicStack {

public:
    DynamicStack() = default;

    DynamicStack(int _size, int value);

    DynamicStack(DynamicStack &other);

    DynamicStack(std::initializer_list<int> list);

    ~DynamicStack();

    void Push(int value);

    int Pop();

    int64_t Size();

    bool Empty();

    int Get();

    bool operator==( const DynamicStack &rhs) const;

    bool operator!=(DynamicStack &rhs) const;

    DynamicStack &operator=(DynamicStack &rhs);


private:
    int *data = nullptr;
    int64_t size;
    int64_t capacity;

    void changeCapacity(int64_t size);
};
