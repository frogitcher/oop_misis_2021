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
	~Stack() {
	Clear();
	}
	Stack(const Stack<T>& stc) {
		*this = stc;
	}
	Stack(Stack<T>&& stc) {
		head = stc.head;
		tail = stc.tail;
		size = stc.size;
     stc.tail = nullptr;
		stc.head = nullptr;
		stc.size = 0;
	}
	Stack(const std::initializer_list<T>& list) {
		for (auto& element : list) {
			Push((T)element);
		}
	}
  void Pop() {
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
	void Push(const T& value) {
		head = new Node{value, head};
		if (tail == nullptr) {
			tail = head;
		}
		size++;
	}
	T& Get() const {
		if (head == nullptr) {
			throw std::length_error("No elements in stack!");
		}
		return head->value;
	}
  
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
 
	void Swap(Stack<T>& stc) {
		std::swap(head, stc.head);
    std::swap(size, stc.size);
		std::swap(tail, stc.tail);
	}
	void Merge(Stack<T>& stc) {
		tail->next = stc.head;
		tail = stc.tail;
		size += stc.size;
    stc.tail = nullptr;
		stc.head = nullptr;
		stc.size = 0;
	}
	void Clear() {
		while (size > 0) {
			Pop();
		}
	}
  
	Stack<T>& operator=(const Stack<T>& stc) {
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
	Stack<T>& operator=(Stack<T>&& stc) {
		return *this = Stack<T>(stc);
	}
	bool operator==(const Stack<T>& stc) const {
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
	inline bool operator!=(const Stack<T>& stc) const {
		return !(*this == stc);
	}
private:
  Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;
};

template <typename T>
inline typename Stack<T>::Node* Get_Head(const Stack<T>& stc);

template <typename T>
inline typename Stack<T>::Node* Get_Tail(const Stack<T>& stc);
