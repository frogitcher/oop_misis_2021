#pragma once
#include <stdexcept>
#include <initializer_list>
#include <cstddef>
#include <utility>

template<typename T>
class Stack {
	struct Node {
		T value;
		Node* next;
	};
public:
	Stack() = default;
	~Stack();
	Stack(const Stack<T>& stc);
	Stack(Stack<T>&& stc);
	Stack(const std::initializer_list<T>& list);
	
	void Pop();
	void Push (const T& value);
	T& Get() const;
	inline size_t Size() const {
		return size;
	}
	inline bool Empty() const {
		return size == 0;
	}
	inline friend Node* Get_Head(const Stack<T>& stc) {
		return stc.head;
	}
	inline friend Node* Get_Tail(const Stack<T>& stc) {
		return stc.tail;
	}
	void Swap(Stack<T>& stc);
	void Merge(Stack<T>& stc);
	void Clear();
	Stack<T>& operator=(const Stack<T>& stc);
	Stack<T>& operator=(Stack<T>&& stc);
	bool operator==(const Stack<T>& stc) const;
	inline bool operator!=(const Stack<T>& stc) const {
		return !(*this == stc);
	};
	
private:
	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;
	void Set_Head(T value, Node* next);
};

template<typename T>
Stack<T>::~Stack() {
	Clear();
}

template<typename T>
T& Stack<T>::Get() const {
	if (head == nullptr) {
		throw std::length_error("Stack is empty!");
	}
	return head->value;
}

template<typename T>
void Stack<T>::Swap(Stack<T>& stc) {
	std::swap(head, stc.head);
	std::swap(tail, stc.tail);
	std::swap(size, stc.size);
}

template<typename T>
Stack<T>::Stack(const Stack<T>& stc) {
	*this = stc;
}

template<typename T>
void Stack<T>::Push(const T& value) {
	Set_Head(value, head);
	if (tail == nullptr) {
		tail = head;
	}
}
template<typename T>
Stack<T>::Stack(const std::initializer_list<T>& list) {
	for (auto el : list) {
		Push((T)el);
	}
}

template<typename T>
void Stack<T>::Pop() {
	if (Empty()) {
		throw std::length_error("Stack is empty!");
	}
	Node* cur = head;
	head = cur->next;
	delete cur;
	if (head == nullptr) {
		tail == nullptr;
	}
	--size;
}


template<typename T>
Stack<T>::Stack(Stack<T>&&stc) {
	head = stc.head;
	tail = stc.tail;
	size = stc.size;
	stc.head = nullptr;
	stc.tail = nullptr;
	stc.size = 0;
}

template<typename T>
void Stack<T>::Merge(Stack<T>& stc) {
	tail->next = stc.head;
	tail = stc.tail;
	size += stc.size;
	stc.head = nullptr;
	stc.tail = nullptr;
	stc.size = 0;
}

template<typename T>
void Stack<T>::Clear() {
	while (size > 0) {
		Pop();
	}
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& stc) {
	Clear();
	if (stc.size != 0) {
		head = new Node{ stc.head->value, nullptr };
		Node* cur = stc.head->next;
		Node* prev = head;
		while (cur != nullptr) {
			prev->next = new Node{ cur->value, nullptr };
			prev = prev->next;
			cur = cur->next;
		}
		tail = prev;
	}
	size = stc.size;
	return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& stc) {
	head = stc.head;
	tail = stc.tail;
	size = stc.size;
	stc.head = nullptr;
	stc.tail = nullptr;
	stc.size = 0;
	return *this;
}

template<typename T>
bool Stack<T>::operator==(const Stack<T>& stc) const {
	if (size != stc.size) {
		return false;
	}
	Node* a = head;
	Node* b = stc.head;
	while (a != nullptr) {
		if (a->value != b->value) {
			return false;
		}
		a = a->next;
		b = b->next;
	}
	return true;
}

template<typename T>
void Stack<T>::Set_Head(T value, Stack::Node* next) {
	head = new Node{ value, next };
	++size;
}
	
template <typename T>
inline typename Stack<T>::Node* Get_Head(const Stack<T>& stc);

template <typename T>
inline typename Stack<T>::Node* Get_Tail(const Stack<T>& stc);
