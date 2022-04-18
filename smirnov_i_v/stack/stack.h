#pragma once
#include <cstdint>
#include <initializer_list>
#include <stdexcept>

template <typename T>
class Stack
{
public:
	struct Node {
		T value;
		Node* next;
	};

	Stack() = default;

	~Stack() {
		while (!Empty()) {
			Pop();
		}
	}

	Stack(const Stack<T>& st) {
		Node* cur = st.head;
		head = cur;
		while (cur != nullptr) {
			tail = new Node(*cur);
			cur = cur->next;
		}
		size = st.size;
	}

	Stack(Stack<T>&& st) {
		head = st.head;
		tail = st.tail;
		size = st.size;
		st.head = nullptr;
		st.tail = nullptr;
		st.size = 0;
	}

	Stack(const std::initializer_list<T>& list) {
		for (auto& it : list) {
			Push(it);
		}
	}

	void Push(const T& value) {
		head = new Node{ value, head };
		if (tail == nullptr) {
			tail = head;
		}
		size++;
	};

	void Pop() {
		if (size == 0) {
			throw std::underflow_error("Stack is already empty!");
		}
		Node* temp = head->next;
		delete head;
		head = temp;
		size--;
	};

	T& Get() const {
		return head->value;
	}

	bool Empty() const {
		return size == 0;
	}

	size_t Size() const {
		return size;
	}

	Node* GetHead() const {
		return head;
	}

	Node* GetTail() const {
		return head;
	}

	void Swap(Stack<T>& st) {
		Node* temp = head;
		head = st.head;
		st.head = temp;
		temp = tail;
		tail = st.tail;
		st.tail = temp;
		size += st.size;
		st.size = size - st.size;
		size -= st.size;
	}

	void Merge(Stack<T>& st) {
		if (!st.Empty()) {
			st.tail->next = head;
			head = st.head;
			size += st.size;
		}
		st.head = nullptr;
		st.tail = nullptr;
		st.size = 0;
	}

	bool operator==(const Stack<T>& st) const {
		if (size != st.size) return false;
		Node* cur1 = head;
		Node* cur2 = st.head;
		while (cur1 != nullptr) {
			if (cur1->value != cur2->value) return false;
			cur1 = cur1->next;
			cur2 = cur2->next;
		}
		return true;
	}

	bool operator!=(const Stack<T>& st) const {
		return !(*this == st);
	}

	Stack<T>& operator=(const Stack<T>& st) {
		while (!Empty()) {
			Pop();
		}
		Node* cur = st.head;
		head = cur;
		while (cur != nullptr) {
			tail = new Node(cur);
			cur = cur.next;
		}
		size = st.size;
		return *this;
	}


private:
	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;
};