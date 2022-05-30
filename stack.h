#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

template <typename T>
struct Node {// Node for Stack
    T value;
    Node* next;
    Node(T _val) : value(_val), next(nullptr) {};
};

template <typename T> class Stack;

template <typename T>
ostream& operator<<(ostream& stream, const Stack<T>& s)
{
	Node<T>* tmp = s.head;
	while (tmp != nullptr) {
		cout << (T)tmp->value << " ";
		tmp = tmp->next;
	}
	cout << "\n";
	return stream;
}

template <typename T>
class Stack {
private:
    Node<T> *head = nullptr, *tail = nullptr;
    size_t size = 0;
public:
    //constructors
	Stack() = default;
	Stack(const Stack<T>& obj);
	~Stack();
    void push(T el);
    void pop();
    T get();
      friend ostream& operator<<<T>(ostream& stream, const Stack&s);
    bool Empty() const;
    size_t Size() const;

    void swap(Stack<T>& st);
    void merge(Stack<T>& s);

    bool operator==(const Stack<T>& s) const;
	bool operator!=(const Stack<T>& s) const;
	Stack& operator=(const Stack<T>& s);
	Stack& operator=(Stack&& s);
};


template<typename T>
void pr(Stack<T>f) {// function for checking constructors and destructor
	cout << "\nFunction pr - show parametr of " << typeid(f).name() << ": ";
	f.show();
	return;
}
