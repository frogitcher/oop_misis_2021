#pragma once
#include <initializer_list>
#include <stddef.h>
template<typename T>
class Stack {
public:
	struct Node {
		T value;
		Node* next;
	};
	Stack() = default;
	Stack(const Stack<T>& other);
	Stack(Stack<T>&& other);
	template<typename T>
	void recursive_copy(Node* p_other_node);
	Stack(const std::initializer_list<T>& list);
	~Stack();
	size_t Size() const;
	T& Get() const;
	bool Empty() const;
	void Push(const T& value);
	void Pop();
	void clear();
	void merge(Stack<T>& other);
	void swap(Stack<T>& other);
	T* begin();
	T* end();
	bool operator==(const  Stack<T>& other) const;
	bool operator!=(const  Stack<T>& other) const;
	Stack& operator=(const Stack<T>& other);
	Stack& operator=(Stack&& other);

private:
	void recursive_copy(Node* other_node);
	bool recursive_compare(const Node* node1, const Node* node2) const;
	size_t size = 0;
	Node* head = nullptr;
	Node* tail = nullptr;
};