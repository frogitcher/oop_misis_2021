#pragma once
#include <initializer_list>
#include <stdexcept>

template <typename T>
class Stack {
public:
	struct Node {
		T value;
		Node* next;
	};

	Stack() = default;
	~Stack() {
		while (size != 0) {
			pop();
		}
	}

	Stack(const Stack<T>& other) {
		*this = other;
	}

	Stack(Stack<T>&& other) {
		head = other.head;
		tail = other.tail;
		size = other.size;
		other.head = nullptr;
		other.tail = nullptr;
		other.size = 0;
	}

	Stack(const std::initializer_list<T>& list) {
		for (T element : list) {
			push(element);
		}
	}

	void push(const T& value) {
		New_Node(value, head);
		if (size == 1) {
			tail = head;
		}
	}

	void pop() {
		if (size == 0) {
			throw std::out_of_range("The size is equal to zero");
		}
		else {
			Node* temp = head->next;
			delete head;
			head = temp;
			if (head == nullptr) {
				tail = head;
			}
			size--;
		}
	}

	void swap(Stack<T>& other) {
		std::swap(head, other.head);
		std::swap(tail, other.tail);
		std::swap(size, other.size);
	}

	void merge(Stack<T>& other) {
		tail->next = other.head;
		tail = other.tail;
		size = size + other.size;
		other.tail = nullptr;
		other.head = nullptr;
		other.size = 0;
	}

	T& get() const {
		if (head == nullptr) {
			throw std::out_of_range("The size is equal to zero");
		}
		return head->value;
	}

	bool empty() const {
		return size == 0;
	}

	size_t Size() const {
		return size;
	}

	bool operator==(const Stack<T>& rhs) const {
		if (size != rhs.size) {
			return false;
		}
		Node* first = head;
		Node* second = rhs.head;
		while (first != nullptr) {
			if (first->value != second->value) {
				return false;
			}
			first = first->next;
			second = second->next;
		}
		return true;
	}

	bool operator!=(const Stack<T>& rhs) const {
		return !operator==(rhs);
	}

	Stack<T>& operator=(const Stack<T>& rhs) noexcept {
		Node* first = head;
		Node* second = rhs.head;
		int add = rhs.size - size;
		for (int i = 0; i < add; i++) {
			push(second->value);
			second = second->next;
		}
		first = head;
		second = rhs.head;
		while (first != nullptr) {
			first->value = second->value;
			first = first->next;
			second = second->next;
		}
		size = rhs.size;
		return *this;
	}

	Stack<T>& operator=(Stack<T>&& other) {
		head = other.head;
		tail = other.tail;
		size = other.size;
		other.head = nullptr;
		other.tail = nullptr;
		other.size = 0;
		return *this;
	}
private: 
	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;

	void New_Node(T value, Node* onhead) {
		head = new Node{ value, onhead };
		++size;
	}
};
