#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

template <typename T>
struct Node {// Node for Stack
    T value;
    Node* next;
    Node(T _val) : value(_val), next(nullptr) {};
};

template <typename T> class Stack;

template <typename T>
ostream& operator<<(ostream& stream, const Stack<T>& s)
{
	Node<T>* tmp = s.head;
	while (tmp != nullptr) {
		cout << (T)tmp->value << " ";
		tmp = tmp->next;
	}
	cout << "\n";
	return stream;
}

template <typename T>
class Stack {
private:
    Node<T> *head = nullptr, *tail = nullptr; 
    size_t size = 0;
public:
    //constructors
	Stack() = default;
	Stack(const Stack& obj) {
		cout << "constr_kopir " << typeid(obj).name() << "\n";
		try {
			if (obj.head == nullptr) {
				size = 0;
				head = nullptr;
				tail = nullptr;
				return;
			}

			Stack<T>tmp_stack; // temporary Stack
			// Копируем стек obj -> tmp_stack
			// получаем значение obj.head
			Node<T>* pNode = obj.head;
			while (pNode != nullptr) {
				// получаем значение очередного узла и добавляем его в стек tmp_stack
				T el = pNode->value;
				tmp_stack.push(el);
				// передвигаемся на следующий узел  в obj (с помощью указателя pNode)
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
	//destructor
	~Stack() {
		cout << "destrucor. Size = " << size << endl;
		if (head == nullptr) return; // если стек пустой
		while (tail != head) {
			this->pop();
		}
		if (head == tail)
		{
			delete head; // если в стеке один элемент
			head = nullptr;
		}
		if (head == nullptr) return;

	}
    void push(T el)
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
    void pop() {
        if (head == tail) {
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
    T get() {
        return head->value;
    }
      friend ostream& operator<<<T>(ostream& stream, const Stack&s);

    void show()
    {
        Node<T>* tmp = head;
        while (tmp != nullptr) {
            cout << (T)tmp->value << " ";
            tmp = tmp->next;
        }
        cout << "\n";
    }

    bool Empty() {
        return (head == nullptr);
    }

    size_t Size() {
        return size;
    }

    void swap(Stack<T>& st) {
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
};


template<typename T>
void pr(Stack<T>f) {// function for checking constructors and destructor
	cout << "\nFunction pr - show parametr of " << typeid(f).name() << ": ";
	f.show();
	return;
}


