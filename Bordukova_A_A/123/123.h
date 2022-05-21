#pragma once
#include <ostream>

template<typename T>
class Queue {
public:
		struct Node {
			 value;
			Node* next;
			Node* prev;
		};
		//consturctors and distructors
		Queue() = default;
		~Queue()
		{
			clear();
		}
		Queue(const Queue<T>& que) {
			*this = que;
		}
		Queue(Queue<T>&& que) {
			head = que.head;
			tail = que.tail;
			size = que.size;
			que.head = nullptr;
			que.tail = nullptr;
			que.size = 0;
		}
		Queue(const std::initializer_list<T>& list) {
			for (auto& element : list) {
				Push((T)element);
			}
		}
		//operations with stack
		void Push(const T& value) {
			Node* q = tail;
			tail = q->next; 
			size++;
		}
		void Pop(const T& value)
		{
			if (Empty()) {
					throw std::length_error("Queue is empty!");
			}
			Node* q = tail;
			tail = q->prev;
			delete q;
			if (tail == nullptr) {
				head == nullptr;
			}
			--size;
		}

		inline bool Empty() const {
			return size == 0;
		}
		inline size_t Size() const {
			return size;
		}
		inline friend Node* Get_Head(const Queue<T>& que) {
			return que.head;
		}
		Queue<T>& operator=(const Queue<T>& que) {
			Clear();
			if (que.size != 0) {
				head = new Node{ que.head->value, nullptr };
				Node* q = que.head->next;
				Node* p = head;
				while (q != nullptr) {
					p->next = new Node{ q->value, nullptr };
					p = p->next;
					q = q->next;
				}
				tail = p;
			}
			size = que.size;
			return *this;
		}
		bool operator==(const Queue<T>& que) const {
			if (size != que.size) {
				return false;
			}
			Node* q1 = head;
			Node* q2 = que.head;
			while (q1 != nullptr) {
				if (q1->value != q2->value) {
					return false;
				}
				q1 = q1->next;
				q2 = q2->next;
			}
			return true;
		}
		inline bool operator!=(const Queue<T>& que) const {
			return !(*this == que);
		}
		void Clear() {
			while (size > 0) {
				Pop();
			}
		}
private:
	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;
};