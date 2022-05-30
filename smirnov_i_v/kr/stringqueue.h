#include <string>
#pragma_once

class StringQueue
{
public:
	struct Node {
		string value;
		Node* next;
		Node(string _value, Node* _next) {
			value = _value;
			next = _next;
		}
	};
	StringQueue() = default;
	StringQueue(initializer_list<string> list);
	~StringQueue();
	void Push(string s);
	void Pop();
	size_t Size() const;
	bool Empty() const;
	string Get() const;
	bool operator==(const StringQueue& rhs) const;
	bool operator!=(const StringQueue& rhs) const;
	StringQueue& operator=(const StringQueue& other);
private:
	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;
};