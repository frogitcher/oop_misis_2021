#pragma once
#include <iostream>
class queue{
private:
	int size = 0;
	int ukaz_on_pred;
	int *ukaz;
	int value;
	int first;
	int last;
public:
	queue() = default;
	void push(int Value) {
		queue *A = new queue;
		A->ukaz_on_pred = *ukaz;
		A->value = Value;
		A->size += 1;
		A->last = Value;
	}
	int Size() {
		return size;
	}
	int get() {
		return last;
	}
	void pop() {
		delete[] this;
	}
	~queue() = default;
};