#pragma once
#include <initializer_list>
#include <cstddef>
#include <utility>
#include <stdexcept>

template<typename T>
class Stack {
	struct Node {
		T value;
		Node* next;
	};

	public:
		//Creating and deliting stack(declaration)
		Stack() = default;
		~Stack();
		Stack(const Stack<T>& stc);
		Stack(Stack<T>&& stc);
		Stack(const std::initializer_list<T>& list);

		//Operations with elemats of stack(declaration)
		void Push(const T& value);
		void Pop();
		T& Get() const;

		//Getting data about stack
		inline bool Empty() const {
			return size == 0;
		}
		inline size_t Size() const {
			return size;
		}
		inline friend Node* Get_Head(const Stack<T>& stc) {
			return stc.head;
		}
		inline friend Node* Get_Tail(const Stack<T>& stc) {
			return stc.tail;
		}

		//Operations with hole stack(declaration)
		void Swap(Stack<T>& stc);
		void Merge(Stack<T>& stc);
		void Clear();

		//Logical operations(declaration)
		Stack<T>& operator=(const Stack<T>& stc);
		Stack<T>& operator=(Stack<T>&& stc);
		bool operator==(const Stack<T>& stc) const;
		inline bool operator!=(const Stack<T>& stc) const {
			return !(*this == stc);
		}

	private:
		Node* head = nullptr;
		Node* tail = nullptr;
		size_t size = 0;
};

//Creating and deliting stack(defenition)
template <typename T>
inline typename Stack<T>::Node* Get_Head(const Stack<T>& stc);

template <typename T>
inline typename Stack<T>::Node* Get_Tail(const Stack<T>& stc);

template <typename T>
Stack<T>::~Stack() {
	Clear();
}

template <typename T>
Stack<T>::Stack(const Stack<T>& stc) {
	*this = stc;
}

template <typename T>
Stack<T>::Stack(Stack<T>&& stc) {
	head = stc.head;
	tail = stc.tail;
	size = stc.size;
	stc.head = nullptr;
	stc.tail = nullptr;
	stc.size = 0;
}

template <typename T>
Stack<T>::Stack(const std::initializer_list<T>& list) {
	for (auto& element : list) {
		Push((T)element);
	}
}

//Operations with elemats of stack(definition)
template <typename T>
void Stack<T>::Push(const T& value) {
	head = new Node{ value, head };
	if (tail == nullptr) {
		tail = head;
	}
	size++;
}

template <typename T>
void Stack<T>::Pop() {
	if (Empty()) {
		throw std::length_error("Stack is empty!");
	}
	Node* q = head;
	head = q->next;
	delete q;
	if (head == nullptr) {
		tail == nullptr;
	}
	--size;
}

template <typename T>
T& Stack<T>::Get() const {
	if (head == nullptr) {
		throw std::length_error("Thare are no elements in stack!");
	}
	return head->value;
}

//Operations with hole stack(definition)
template <typename T>
void Stack<T>:: Swap(Stack<T>& stc) {
	std::swap(head, stc.head);
	std::swap(tail, stc.tail);
	std::swap(size, stc.size);
}

template <typename T>
void Stack<T>::Merge(Stack<T>& stc) {
	if (stc.head != nullptr) 
	{
		tail->next = stc.head;
		tail = stc.tail;
		size += stc.size;
		stc.head = nullptr;
		stc.tail = nullptr;
		stc.size = 0;
	}
}

template <typename T>
void Stack<T>::Clear() {
	while (size > 0) {
		Pop();
	}
}

//Logical operations(definition)
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& stc) {
	Clear();
	if (stc.size != 0) {
		head = new Node{ stc.head->value, nullptr };
		Node* q = stc.head->next;
		Node* p = head;
		while (q != nullptr) {
			p->next = new Node{ q->value, nullptr };
			p = p->next;
			q = q->next;
		}
		tail = p;
	}
	size = stc.size;
	return *this;
}

template <typename T>
Stack<T> & Stack<T>:: operator=(Stack<T>&& stc) {
	Clear();
	head = stc.head;
	tail = stc.tail;
	size = stc.size;
	stc.head = nullptr;
	stc.tail = nullptr;
	stc.size = 0;
	return *this = Stack<T>(stc);
}

template <typename T>
bool Stack<T>:: operator==(const Stack<T>& stc) const {
	if (size != stc.size) {
		return false;
	}
	Node* q1 = head;
	Node* q2 = stc.head;
	while (q1 != nullptr) {
		if (q1->value != q2->value) {
			return false;
		}
		q1 = q1->next;
		q2 = q2->next;
	}
	return true;
}