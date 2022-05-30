#include <stack.h>

template<typename T>
Stack<T>::Stack(const Stack<T>& obj); {
		cout << "constr_kopir " << typeid(obj).name() << "\n";
		try {
			if (obj.head == nullptr) {
				size = 0;
				head = nullptr;
				tail = nullptr;
				return;
			}

			Stack<T>tmp_stack;
			Node<T>* pNode = obj.head;
			while (pNode != nullptr) {
				T el = pNode->value;
				tmp_stack.push(el);
				pNode = pNode->next;
			}

			// Копируем стек tmp_stack -> this
			while (!tmp_stack.Empty()) {
				T el = tmp_stack.get();
				push(el);
				tmp_stack.pop();
			}
		}
		catch (bad_alloc e)
		{
			// Если память выделить не удалось, то вывести системное сообщение
			cout << "Error in constructor: " << e.what() << endl;
		}
		cout << "constr_konec" << "\n";
	}

template <typename T>
Stack<T>::~Stack() {
		cout << "destrucor. Size = " << size << endl;
		if (head == nullptr) return; // если стек пустой
		while (tail != head) {
			this->pop();
		}
		if (head == tail)
		{
			delete head; // если в стеке один элемент
			head = nullptr;
			tail = nullptr;
		}
	}

template <typename T>
void Stack<T>::push(T el)
    {
        Node<T>* p = new Node <T>{ el };
        if (!size) {
            head = p;
            tail = p;
            size++;
            return;
        }
        p->next = head;
        head = p;

        size++;
        return;
    }

template <typename T>
void Stack<T>::pop() {
        if (head == tail && head != nullptr) {
            delete head;
            head = nullptr;
            tail = nullptr;
            size--;
            return;
        }
        Node<T>* tmp = head->next;
        delete head;
        head = tmp;
        size--;
        return;
    }

template<typename T>
T Stack<T>::get() {
        return head->value;
    }

template<typename T>
bool Stack<T>::Empty() const{
        return (head == nullptr);
}

template<typename T>
size_t Stack<T>::Size() const{
        return size;
    }

template<typename T>
void Stack<T>::swap(Stack<T>& st) {
        Node<T>* tmp = new Node<T>(0);
        tmp = head;
        head = st.head;
        st.head = tmp;
        tmp = tail;
        tail = st.tail;
        st.tail = tmp;
        size_t i;
        i = size;
        size = st.size;
        st.size = i;
        return;
    }

template<typename T>
bool Stack<T>::operator==(const Stack<T>& s) const
{
	Node<T>* n1 = s.head;
	Node<T>* n2 = this.head;
	if (this->size != s.size) {
		return false;
	}
	while (n1 != nullptr) {
		if (n1.value != n2.value) {
			return false;
		}
		n1 = n1.next;
		n2 = n2.next;
	}
	return true;
}

template<typename T>
bool Stack<T>::operator!=(const Stack<T>& s) const
{
	return !(*this == s);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& s)
{
	clear();
	Node* n = s.head;
	for (size_t i = 0; i < s.Size(); i++) {
		this.Push(n.value);
		n = n.next;
	}
	return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& s)
{
	if (&s == this) return *this;
	this.clear();
	this.swap(other);
	other.clear();
	return *this;
}

template<typename T>
void Stack<T>::merge(Stack<T>& s)
{
	if (!s.Empty()) {
		s.tail.next = head;
		head = s.head;
		size += s.size;
	}
	s.head = nullptr;
	s.tail = nullptr;
	s.size = 0;
}


















