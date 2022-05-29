#pragma once
#include <initializer_list>
#include <stdexcept>

template <typename T>
class Stack {

	struct Node{
		T value;
		Node* next;
	};
	public:

	Stack() = default;
	~Stack();
	Stack(const Stack<T>& st);
	Stack(Stack<T>&& st);
	Stack(const std::initializer_list<T>& list);
	void Push(const T& value);
	void Pop();
	void Clear();
	T& Get() const;
	bool Empty() const;
	size_t Size() const;
	void swap(Stack<T>& st);
	void merge(Stack<T>& st);
	bool operator==(const Stack<T>& st) const;
	bool operator!=(const Stack<T>& st) const;
	Stack<T>& operator=(const Stack<T>& st);
	Stack<T>& operator=(Stack<T>&& st);

	
	private:

	
	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size=0;
	
};

template <typename T>
Stack<T>::Stack(const Stack<T>& st) {
	*this = st;
}

template <typename T>
Stack<T>::Stack(Stack<T>&& st) {
	Clear();
	head = st.head;
	tail = st.tail;
	size = st.size;
	st.head=nullptr;
	st.size=0;
	st.tail=nullptr;
}

template <typename T>
Stack<T>::Stack(const std::initializer_list<T>& list){
	for (auto i: list){
		Push(i);
	}
}

template <typename T>
Stack<T>::~Stack(){
	while (size>0){
		Pop();
	}
}

template <typename T>
void Stack<T>::Clear(){
	while (size>0){
		Pop();
	}
}
template <typename T>
void Stack<T>::Pop(){
	if (size==0){
		throw "Nothing to pop";
	}
	if (size>0){
		Node* lambda_head = head->next;
		delete head;
		head = lambda_head;
		//delete lambda_head;
		size-=1;
		if (size==0){
			tail = nullptr;
		}
	}
}

template <typename T>
void Stack<T>::Push(const T& value){
	head = new Node { value, head };
	if (tail==nullptr){
		tail = head;
	}
	size = size+1;
}

template <typename T>
bool Stack<T>::Empty() const{
	return size==0;
}

template <typename T>
T& Stack<T>::Get() const{
	if (head==nullptr){
		throw "Stack is empty";
	}
	return head->value;
}

template <typename T>
size_t Stack<T>::Size() const{
	return size;
}

template <typename T>
void Stack<T>::swap(Stack<T>& st){
	std::swap(head,st.head);
	std::swap(tail,st.tail);
	std::swap(size,st.size);
}

template <typename T>
void Stack<T>::merge(Stack<T>& st){
	tail->next = st.head;
	tail = st.tail;
	size = size + st.size;
	st.head = nullptr;
	st.tail = nullptr;
	st.size = 0;
}

template <typename T>
bool Stack<T>::operator==(const Stack<T>& st) const{
	if (size!=st.size){
		return false;
	}
	if (size==st.size && size==0){
		return true;
	}
	if (head->value == st.head->value){
		Node* a = head->next;
		Node* b = st.head->next;
		for (int i=1;i<size;i++){
			if (a->value!=b->value){
				return false;
			}
			a = a->next;
			b = b->next;
		}
	}
	else{
		return false;
	}
	return true;
}

template <typename T>
bool Stack<T>::operator!=(const Stack<T>& st) const{
	return !(*this==st);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& st){
	Clear();
	/*if (st.size==0){
		head = nullptr;
		tail = head;
	}*/
	if (st.size >0){
		head = new Node { st.head->value, nullptr };
		Node* a = st.head->next;
		Node* b = head;
		for (int i=1;i<st.size;i++){
			b->next = new Node{ a->value, nullptr };
			a = a->next;
			b = b->next;
		}
		tail = b;
	}
		size = st.size;
	return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& st){
	head = st.head;
	tail = st.tail;
	size = st.size;
	st.head=nullptr;
	st.tail=nullptr;
	st.size=0;
}