#pragma once
#include <initializer_list>
#include <stdexcept>
template<typename T>
class Stack
{
public:
	struct Node
	{
		T value;
		Node* next;
	};

	Stack() = default;

	Stack(const Stack<T>& other)
	{
		*this = other;
	}

	Stack(Stack<T>&& other)
	{
		first = other.first;
		last = other.last;
		size = other.size;
		other.first = nullptr;
		other.last = nullptr;
		other.size = 0;
	}

	Stack(const std::initializer_list<T>& list)
	{
		for (T elem : list)
		{
			Push(elem);
		}
	}

	~Stack()
	{
		while (size > 0)
		{
			Pop();
		}
	}
	void Push(const T& elem)
	{
		first = new Node{ elem,first };
		if (last==nullptr)
		{
			last = first;
		}
		size++;
	}

	void Pop()
	{
		if (size == 0)
		{
			throw std::out_of_range("stack contains no attributes");
		}
		else
		{
			Node* temp = first->next;
			delete first;
			if (first == nullptr)
			{
				last = first;
			}
			first = temp;
			size--;
		}
	}

	bool Empty() const
	{
		return (size == 0);
	}
	T& Get() const
	{
		if (first == nullptr)
		{
			throw std::out_of_range("Size is equal to zero");
		}
		return first->value;
	}

	size_t Size() const
	{
		return size;
	}

	void Clear()
	{
		while (size > 0)
		{
			Pop();
		}
		first = nullptr;
		last = nullptr;
	}

	void Swap(Stack<T>& other)
	{
		Node* temp = first;
		first = other.first;
		other.first = temp;
		temp = last;
		last = other.last;
		other.last = temp;
		size_t s = size;
		size = other.size;
		other.size = s;
	}

	Stack<T>& operator=(const Stack<T>& other)
	{
		while (!Empty())
		{
			Pop();
		}
		first = new Node{other.first->value, nullptr};
		Node* current = other.first->next;
		Node* previous = first;
		while (current != nullptr)
		{
			previous->next = new Node{current->value, nullptr};
			previous = previous->next;
			current = current->next;
		}
		last = previous;
		size = other.size;
		return *this;
	}
	bool operator==(const Stack<T> other) const
	{
		if (size != other.size)
		{
			return false;
		}
		Node* elem1 = first;
		Node* elem2 = other.first;
		while (elem1 != nullptr)
		{
			if (elem1->value != elem2->value)
			{
				return false;
			}
			elem1 = elem1->next;
			elem2 = elem2->next;
		}
		return true;
	}
	bool operator!=(const Stack<T> other) const
	{
		return !(*this == other);
	}

	void Merge(Stack<T>& other)
	{
		last->next = other.first;
		last = other.last;
		size += other.size;
		other.last = nullptr;
		other.first = nullptr;
		other.size = 0;
	}
private:
	size_t size = 0;
	Node* first = nullptr;
	Node* last = nullptr;
};
