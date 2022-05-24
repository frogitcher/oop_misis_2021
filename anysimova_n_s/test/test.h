#pragma once
#include <initializer_list>
#include <iostream>

class Queue {
public:

	struct Node {
		int value;
		Node* next;
	};

	Queue(int size_ = 0, int value = 0);
	Queue(const Queue& other);
	Queue(std::initializer_list<int> list);
	~Queue();
	
	void Push(int value);
	void Resize(int size__);
	int Pop();
	int Get();
	int Size();

	bool empty();
	bool operator==(const Queue& other) const;
	bool operator!=(const Queue& other) const;


private:
	int size = 0;
	Node* head = nullptr;
	Node* tail = nullptr;
};

