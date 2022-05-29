#pragma once
#include <initializer_list>
#include <stdexcept>
template <typename T>
class Stack {
public:
	struct Node{
		T value;
		Node* next;
	};

	Stack() = default;
	Stack(const std::initializer_list<T>& list);
	Stack(const Stack<T>& other);
	Stack(Stack<T>&& other);
	~Stack();

	size_t Size() const;
	bool Empty() const;

	void Push(const T& value);
	void Pop();
	T& Get() const;

	bool operator==(const Stack<T>& other) const;
	bool operator!=(const Stack<T>& other) const;

	Stack<T>& operator=(const Stack<T>& other);

	void Clear();
	void Swap(Stack<T>& other);
	void Merge(Stack<T>& other);
private:
	size_t size = 0;
	Node* head = nullptr;
	Node* tail = nullptr;
};

template <typename T>
size_t Stack<T>::Size() const{
	return size;
}

template <typename T>
bool Stack<T>::Empty() const{
	return size==0;
}

template <typename T>
void Stack<T>::Push(const T& value){
	head = new Node{value, head};
	if (Empty()) {
		tail = head;
	}
	++size;
}

template <typename T>
void Stack<T>::Pop() {
	if (Empty()) {
		throw std::invalid_argument("Stack is empty!");
	}
	else {
		if (size == 1) {
			tail = nullptr;
		}
		Node* new_head = head->next;
		delete head;
		head = new_head;
		--size;
	}
}

template <typename T>
T& Stack<T>::Get() const{
	if (Empty()) {
		throw std::invalid_argument("Stack is empty!");
	}
	return head->value;
}

template <typename T>
Stack<T>::Stack(const std::initializer_list<T>& List) {
	size = 0;
	for (auto i: List) {
		Push(i);
	}
}

template <typename T>
Stack<T>::Stack(const Stack<T>& other) {
	*this = other;
}

template <typename T>
Stack<T>::Stack(Stack<T>&& other) {
	head = other.head;
	tail = other.tail;
	size = other.Size();

	other.head = nullptr;
	other.tail = nullptr;
	other.size = 0;
}

template <typename T>
Stack<T>::~Stack() {
	Clear();
}

template <typename T>
bool Stack<T>::operator==(const Stack<T>& other) const{
	if (size != other.Size()) {
		return false;
	}
	else {
		Node* first = head;
		Node* second = other.head;
		for (int i=0; i<size; i++) {
            if (first->value != second->value) {
                return false;
            }
            else {
                first = first->next;
                second = second->next;
            }
		}
		return true;
	}
}

template <typename T>
bool Stack<T>::operator!=(const Stack<T>& other) const{
	return not(*this == other);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {

	Clear();
	if (other.Size() > 0) {
        head = new Node{other.head->value, nullptr};
        Node* first = head;
        Node* second = other.head->next;
        while (second != nullptr) {
            first->next = new Node{second->value, nullptr};
            first = first->next;
            second = second->next;
        }
        tail = first;
	}
	size = other.Size();
	return *this;

}

template <typename T>
void Stack<T>::Clear() {
	while (not Empty()) {
		Pop();
	}
}

template <typename T>
void Stack<T>::Swap(Stack<T>& other) {
	std::swap(size, other.size);
	std::swap(head, other.head);
	std::swap(tail, other.tail);
}

template <typename T>
void Stack<T>::Merge(Stack<T>& other) {
	tail->next = other.head;
	tail = other.tail;
	size = size + other.Size();

	other.head = nullptr;
	other.tail = nullptr;
	other.size = 0;
}
