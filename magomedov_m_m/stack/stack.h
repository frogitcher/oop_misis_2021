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

template <typename T>
Stack<T>::~Stack() {
	(*this).Del();
}

template <typename T>
Stack<T>::Stack(const Stack<T>& other) {
	*this = other;
}

template <typename T>
Stack<T>::Stack(Stack<T>&& other) {
	size = other.size;
	head = other.head;
	tail = other.tail;
	other.size=0;
	other.head=nullptr;
	other.tail=nullptr;
}

template <typename T>
Stack<T>::Stack(const std::initializer_list<T>& list) {
	for (T item : list) {
		(*this).Push(item);
	}
}

template <typename T>
void Stack<T>::Push(const T& value) {
	head = new Node{ value,head };
	if (tail == nullptr) {
		tail = head;
	}
	size++;
}

template <typename T>
void Stack<T>::Pop() {
	if (size == 0) {
		throw std::out_of_range("You went out of the stack");
	}
	if (size == 1) {
		tail = nullptr;
	}
	Node* f = (*head).next;
	delete head;
	head = f;
	size--;
}

template <typename T>
T& Stack<T>::Get() const {
	if (size == 0) {
		throw std::length_error("You went out of the stack");
	}
	return (*head).value;
}

template <typename T>
bool Stack<T>::Empty() const {
	return size == 0;
}

template <typename T>
size_t Stack<T>::Size() const {
	return size;
}

template <typename T>
void Stack<T>::Swap(Stack<T>& other)
{
	std::swap(head, other.head);
	std::swap(tail, other.tail);
	std::swap(size, other.size);
}

template <typename T>
bool Stack<T>::operator==(const Stack<T>& other) const {
	if (this->size != other.size) {
		return false;
	}
	Node* i2 = other.head;
	for (Node* i = head;i != nullptr;i = i->next, i2 = i2->next) {
		if (i->value != i2->value) {
			return false;
		}
	}
	return true;
}

template <typename T>
bool Stack<T>::operator!=(const Stack<T>& other) const {
	return !(*this == other);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
	(*this).Del();
	if (other.Size() != 0) {
		head = new Node{ other.head->value, nullptr };
		Node* f = head;
		for (Node* i = other.head->next;i != nullptr;i = (*i).next, f = (*f).next) {
			(*f).next = new Node{ i->value,nullptr };
			if ((*i).next == nullptr) {
				tail = (*f).next;
			}
		}
	}
	size = other.Size();
	return *this;
}

template <typename T>

void  Stack<T>::merge(Stack<T>& other) {
	size += other.size;
	other.tail->next = head;
	head = other.head;
	other.size = 0;
	other.head = nullptr;
	other.tail = nullptr;
}

template <typename T>
void Stack<T>::Del() {
	while (size>0) {
		(*this).Pop();
	}
}

/*std::istream& operator>>(std::istream& input, Rational& rhs);
std::ostream& operator<<(std::ostream& output, const Rational& rhs);*/
