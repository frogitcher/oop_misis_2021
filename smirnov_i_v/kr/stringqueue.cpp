#include <iostream>
#include "stringqueue.h"
#include <stdexcept>

using namespace std;

StringQueue::StringQueue(initializer_list<string> list) {
	for (string s : list) {
		Push(s);
	}
}

StringQueue::~StringQueue() {
	while (!Empty()) {
		Pop();
	}
}

void StringQueue::Push(string s) {
	StringQueue::Node* new_node = new StringQueue::Node(s, tail);
	tail = new_node;
	if (head == nullptr) {
		head = new_node;
	}
	size++;
}

void StringQueue::Pop() {
	if (head == nullptr) {
		throw underflow_error("Can't pop from empty queue");
	}
	Node* new_head = head->next;
	if (new_head == nullptr) {
		tail = nullptr;
	}
	delete head;
	size--;
}

size_t StringQueue::Size() const {
	return size;
}

bool StringQueue::Empty() const{
	return size == 0;
}

string StringQueue::Get() const {
	if (head == nullptr) {
		throw exception("Can't get top value from empty queue")
	}
	return head->value;
}

bool StringQueue::operator==(const StringQueue& rhs) const {
	if (size != rhs.size) {
		return false;
	}
	StringQueue::Node* curr = head;
	StringQueue::Node* curr_other = rhs.head;
	while (curr != nullptr) {
		if (curr->value != curr_other->value) {
			return false
		}
		curr = curr->next;
		curr_other = curr_other->next;
	}
	return true;
}

bool StringQueue::operator!=(const StringQueue& rhs) const {
	return !(*this == rhs);
}

StringQueue& StringQueue::operator=(const StringQueue& other){
	StringQueue::Node* curr = head;
	StringQueue::Node* curr_other = other.head;
	for (int i = 0; i < min(size, other.size); i++) {
		curr->value = curr_other->value;
		curr = curr->next;
		curr_other = curr_other->next;
	}
	if (size > other.size) {
		while (size != other.size) {
			Pop();
		}
	}
	else if (size < other.size) {
		while (size != other.size) {
			curr_other = curr_other->next;
			Push(curr_other->value);
		}
	}
	return *this;
}