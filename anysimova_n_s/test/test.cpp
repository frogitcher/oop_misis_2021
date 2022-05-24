#include "test.h"

Queue::Queue(int size_, int value) {
	for (int i = 0; i < size_; i++) {
		Push(value);
	}
}

Queue::Queue(std::initializer_list<int> list) {
	for (auto elem : list) {
		Push(elem);
	}
}


Queue::~Queue() {
	while (!empty()) {
		Pop();
	}
}

bool Queue::empty() {
	return size == 0;
}

int Queue::Size() {
	return size;
}

void Queue::Push(int value) {
	if (head != nullptr) {
		Node* temp = tail;
		tail = new Node{ value, tail->next };
		temp->next = tail;
		size++;
	}
	else {
		head = new Node{ value, nullptr };
		tail = head;
		size++;
	}
}

int Queue::Pop() {
	Node* temp = head->next;
	int value = head->value;
	delete head;
	head = temp;
	size--;
	return value;
}

int Queue::Get() {
	return head->value;
}


