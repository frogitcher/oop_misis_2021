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
	Stack() = default;
	Stack(const Stack<T>& st);
	Stack(Stack<T>&& st);
	Stack(const std::initializer_list<T>& list);
	~Stack();

	void Push(const T& value);
	void Pop();
	T& Get() const;
	inline bool Empty() const {
		return size == 0;
	}
	inline size_t Size() const {
		return size;
	}
	void Swap(Stack<T>& st);
	void Merge(Stack<T>& st);


	Stack<T>& operator=(const Stack<T>& st);
	Stack<T>& operator=(Stack<T>&& st);

	bool operator==(const Stack<T>& st) const;
	inline bool operator!=(const Stack<T>& st) const;

	inline friend Node* Get_Head(const Stack<T>& st) {
			return st.head;
		}
		inline friend Node* Get_Tail(const Stack<T>& st) {
			return st.tail;
		}
private:
	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;

};


template<typename T>
	Stack<T>::Stack() = default;

	template<typename T>
	Stack<T>::~Stack() {
		while (!(Empty())) {
			Pop();
		}
	}
	template<typename T>
	Stack<T>::Stack(const Stack<T>& other) {
		*this = other;
	}
	template<typename T>
	Stack<T>::Stack(Stack<T>&& other) {
		head = other.head;
		tail = other.tail;
		size = other.size;
		other.head = nullptr;
		other.tail = nullptr;
		other.size = 0;
	}
	template<typename T>
	Stack<T>::Stack(const std::initializer_list<T>& list) {
		for (auto& el : list) {
			Push(el);
		}
	}

	template<typename T>
	void Stack<T>::Push(const T& value) {
		head = new Node{ value, head };
		if (tail == nullptr) {
			tail = head;
		}
		size++;
	}
	template<typename T>
	void Stack<T>::Pop() {
		if (Empty()) {
			throw std::invalid_argument("Invalid size");
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
	T& Stack<T>::Get() const {
		if (head == nullptr) {
			throw std::length_error("Stack is empty!");
		}
		return head->value;
	}
	template<typename T>
	void Stack<T>::Swap(Stack<T>& st) {
		std::swap(head, st.head);
		std::swap(tail, st.tail);
		std::swap(size, st.size);
	}
	template<typename T>
	void Stack<T>::Merge(Stack<T>& st) {
		if (!st.Empty()) {
			st.tail->next = head;
			head = st.head;
			size += st.size;
		}
		st.head = nullptr;
		st.tail = nullptr;
		st.size = 0;
	}
	template<typename T>
	inline bool Stack<T>::Empty() const {
		return size == 0;
	}
	template<typename T>
	inline size_t Stack<T>::Size() const {
		return size;
	}

	template<typename T>
	Stack<T>& Stack<T>::operator=(const Stack<T>& st) {
		while (!(Empty())) {
			Pop();
		}
		if (st.size != 0) {
			head = new Node{ st.head->value, nullptr };
			Node* now = st.head->next;
			Node* then = head;
			while (now != nullptr) {
				then->next = new Node{ now->value, nullptr };
				then = then->next;
				now = now->next;
			}
			tail = then;
		}
		size = st.size;
		return *this;
	}
	template<typename T>
	Stack<T>& Stack<T>::operator=(Stack<T>&& st) {
		head = st.head;
		tail = st.tail;
		size = st.size;
		st.head = nullptr;
		st.tail = nullptr;
		st.size = 0;
	}
	template<typename T>
	bool Stack<T>::operator==(const Stack<T>& st) const {
		if (size != st.size) {
			return false;
		}
		Node* first = head;
		Node* second = st.head;
		while (first != nullptr) {
			if (first->value != second->value) { return false; }
			first = first->next;
			second = second->next;

		}
		return true;
	}
	template<typename T>
	inline bool Stack<T>::operator!=(const Stack<T>& st) const {
		return !(*this == st);
	}
	

