#pragma once
#include <initializer_list>
#include <cstdint>

template <typename T>
class Stack {
public:
	struct Node {
		T value;
		Node* next;
	};
	Stack() = default;
	~Stack();
	Stack(const Stack<T>& other);
	Stack(Stack<T>&& other);
	Stack(const std::initializer_list<T>& list);
	void Push(const T& value);
	void Pop();
	T& Get() const;
	bool Empty() const;
	size_t Size() const;
	void Swap(Stack<T>& other);
	bool operator==(const Stack<T>& other) const;
	bool operator!=(const Stack<T>& other) const;
	Stack<T>& operator=(const Stack<T>& other);
	void merge(Stack<T>& other);
	void Del();
public:
	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;
};


/*std::istream& operator>>(std::istream& input, Rational& rhs);
std::ostream& operator<<(std::ostream& output, const Rational& rhs);*/