#pragma once


class st {
public:
	st() = default;
	st(int new_size);
	~st();

	void Push(int value);
	int Pop(int value);
	size_t getsize() const;
	int Get() const;

	int* begin();
	int* end();


	bool operator==(const st& other) const;
	bool operator!=(const st& other) const;
	st& operator=(const st& other);




	bool Empty();

private:
	int* data = nullptr;
	size_t sz = 0;
	size_t capacity = 0;
	void reallocate(int new_size = 0);
};