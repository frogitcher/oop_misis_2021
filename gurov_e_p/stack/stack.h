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
		Stack(const Stack<T>& st) {
			*this = st;
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
			for (auto& el : list) {
				Push((T)el);
			}
		}
		~Stack() {
			Clear();
		}

		void Push(const T& value) {
			Set_Head(value, head);
			if (tail == nullptr) {
				tail = head;
			}
		}
		void Pop() {
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
		T& Get() const {
			if (head == nullptr) {
				throw std::length_error("Stack is empty!");
			}
			return head->value;
		}
		inline bool Empty() const {
			return size == 0;
		}
		inline size_t Size() const {
			return size;
		}
		void Swap(Stack<T>& st) {
			std::swap(head, st.head);
			std::swap(tail, st.tail);
			std::swap(size, st.size);
		}
		void Merge(Stack<T>& st) {
			tail->next = st.head;
			tail = st.tail;
			size += st.size;
			st.head = nullptr;
			st.tail = nullptr;
			st.size = 0;
		}
		void Clear() {
			while (size > 0) {
				Pop();
			}
		}

		Stack<T>& operator=(const Stack<T>& st) {
			Clear();
			if (st.size != 0) {
				head = new Node{ st.head->value, nullptr };
				Node* cur = st.head->next;
				Node* prev = head;
				while (cur != nullptr) {
					prev->next = new Node{ cur->value, nullptr };
					prev = prev->next;
					cur = cur->next;
				}
				tail = prev;
			}
			size = st.size;
			return *this;
		}
		Stack<T>& operator=(Stack<T>&& st) {
			return *this = Stack<T>(st);
		}

		bool operator==(const Stack<T>& st) const {
			if (size != st.size) {
				return false;
			}
			Node* a = head;
			Node* b = st.head;
			while (a != nullptr) {
				if (a->value != b->value) {
					return false;
				}
				a = a->next;
				b = b->next;
			}
			return true;
		}
		inline bool operator!=(const Stack<T>& st) const {
			return !(*this == st);
		}

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

		void Set_Head(T value, Node* next) {
			head = new Node{ value, next };
			++size;
		}
};

template <typename T>
inline typename Stack<T>::Node* Get_Head(const Stack<T>& st);

template <typename T>
inline typename Stack<T>::Node* Get_Tail(const Stack<T>& st);
