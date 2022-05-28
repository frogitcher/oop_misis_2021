#pragma once
#include <cstdint>
#include <initializer_list>

template <typename T>
class Stack
{
public:
	struct Node {
		T value;
		Node* next;
	};

	Stack() = default;
	~Stack();
	Stack(const Stack<T>& st);
	Stack(Stack<T>&& st);
	Stack(const std::initializer_list<T>& list);
	void Push(const T& value);
	void Pop();
	T& Get() const;
	bool Empty() const;
	size_t Size() const;
	Node* GetHead() const;
	Node* GetTail() const;
	void Swap(Stack<T>& st);
	void Merge(Stack<T>& st);
	bool operator==(const Stack<T>& st) const;
	bool operator!=(const Stack<T>& st) const;
	Stack<T>& operator=(const Stack<T>& st);

private:
	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;
};