#pragma once


class vector {
public:
	vector() = default;
	~vector();
	vector(int size);
	vector(vector& other);
	vector operator=(vector& other);



	bool operator==(const vector& other) const;//
	bool operator!=(const vector& other) const;//

	double operator[](int i);//
	double operator at();//

	int Size();//
	vector operator+(const vector& other) const;//
	vector operator-(const vector& other) const;//
	vector operator*(double scale) const;//
	double norm();//
	vector operator*(const vector& other) const;//

	void operator+=(const vector& other);
	void operator-=(const vector& other);
	void operator*=(const vector& other);
	void operator*=(double scale);


private:
	double* data = new data[];
	size_t size;
	//dont need capacity
};
