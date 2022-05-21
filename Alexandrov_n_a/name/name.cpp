#include "name.h"
void queue::push(int Value) {
	queue* A = new queue;
	A->ukaz_on_pred = *ukaz;
	A->value = Value;
	A->size += 1;
	A->last = Value;
}
int queue::Size() {
	return size;
}
int queue::get() {
	return last;
}
void queue::pop() {
	delete[] this;
}