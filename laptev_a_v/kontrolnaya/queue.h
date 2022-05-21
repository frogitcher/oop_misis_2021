#pragma once
#include <ostream>
#include <initializer_list>
#include <vector>
class Queue{

public:
	Queue() = default;
	Queue(const Queue& qu);
	Queue(Queue& qu);
	Queue::Queue(const std::initializer_list<int>& list) {
		for (int el : list) {
			data.push_back(el);
		}
	}
	~Queue() {
		while (data.size() > 0) {
			delete data[i];
		}
	}
	void Push(int value) {
		data.push_back(value);
	};
	void Pop() {
		data.pop_back();
	}
	void Get() const {
		return (data.end());
	}
	bool Empty() const{
		return data.size() == 0;
	}
	int Size() const{
		return data.size();
	}
	bool operator==(const Queue& qu) {
		if (Size() != qu.Size()) {
			return false;
		}
	}
private:
	std::vector<int> data;
}
