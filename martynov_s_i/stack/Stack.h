#pragma once
#include <initializer_list>

template <typename T>
class Stack {
public:
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
	void Swap(Stack<T>& st);
	bool operator==(const Stack<T>& st) const;
	bool operator!=(const Stack<T>& st) const;
	Stack<T> operator=(const Stack<T>& st);
	void Merge(Stack<T>& st);
	struct Node {
		T value;
		Node* next;
	};
private:
	size_t size = 0;
	Node* head = nullptr;
	Node* tail = nullptr;
	void Clear();
};

template <typename T>
void Stack<T>::Clear() {
	while (head != nullptr) {
		Node* temp = head->next;
		delete head;
		head = temp;
	}
	tail = nullptr;
	size = 0;
}

template <typename T>
Stack<T>::Stack(const std::initializer_list<T>& list) {
	for (size_t i = 0; i < list.size(); ++i) {
		(*this).Push(*(list.begin() + i));
	}
	size = list.size();
}

template <typename T>
Stack<T>::Stack(const Stack<T>& st) {
	size = st.size;
	if (st.head == nullptr) {
		head = nullptr;
		tail = nullptr;
	}
	else {
		Node* new_noda = new Node({ st.head->value, nullptr });
		head = new_noda;
		Node* temp = head;
		Node* st_temp = st.head->next;
		for (size_t i = 1; i < st.size; ++i) {
			new_noda = new Node({ st_temp->value, nullptr });
			temp->next = new_noda;
			temp = temp->next;
			st_temp = st_temp->next;
		}
		tail = new_noda;
	}
}

template <typename T>
void Stack<T>::Swap(Stack<T>& st) {
	std::swap(head, st.head);
	std::swap(tail, st.tail);
	std::swap(size, st.size);
}

template <typename T>
Stack<T>::~Stack() {
	Clear();
}

template <typename T>
void Stack<T>::Push(const T& value) {
	Node* new_noda = new Node({ value, head });
	head = new_noda;
	if (size == 0) {
		tail = head;
	}
	++size;
}

template <typename T>
void Stack<T>::Pop() {
	if (size == 0) {
		throw "size = 0";
	}
	Node* temp = head->next;
	delete head;
	head = temp;
	if (size == 1) {
		tail = head;
	}
	--size;
}

template <typename T>
T& Stack<T>::Get() const {
	if (size == 0) {
		throw "size 0";
	}
	return head->value;
}

template <typename T>
size_t Stack<T>::Size() const {
	return size;
}

template <typename T>
bool Stack<T>::Empty() const {
	return size == 0;
}

template <typename T>
bool Stack<T>::operator==(const Stack& st) const {
	if (size != st.size) {
		return false;
	}
	Node* temp_this = head;
	Node* temp_st = st.head;
	for (size_t i = 0; i < size; ++i) {
		if ((temp_this->value) != (temp_st->value)) {
			return false;
		}
		temp_this = temp_this->next;
		temp_st = temp_st->next;
	}
	return true;
}

template <typename T>
bool Stack<T>::operator!=(const Stack& st) const {
	return !(*this == st);
}

template <typename T>
void Stack<T>::Merge(Stack<T>& st) {
	tail->next = st.head;
	tail = st.tail;
	size += st.size;
	st.tail = nullptr;
	st.head = nullptr;
	st.size = 0;
}

template <typename T>
Stack<T> Stack<T>::operator=(const Stack<T>& st) {
	Clear();
	size = st.size;
	if (st.head == nullptr) {
		head = nullptr;
		tail = nullptr;
		return* this;
	}
	Node* new_noda = new Node({st.head->value, nullptr});
	head = new_noda;
	Node* temp = head;
	Node* st_temp = st.head->next;
	for (size_t i = 1; i < st.size; ++i) {
		new_noda = new Node({st_temp->value, nullptr});
		temp->next = new_noda;
		temp = temp->next;
		st_temp = st_temp->next;
	}
	tail = new_noda;
	return *this;
}

template <typename T>
Stack<T>::Stack(Stack<T>&& st) {
	head = st.head;
	tail = st.tail;
	size = st.size;
	st.head = nullptr;
	st.tail = nullptr;
	st.size = 0;
}


