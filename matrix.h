#include <initializer_list>
#include <stdexcept>
#include <algorithm>

template <typename T>
class Matrix {
public:
	Matrix() = default;
	Matrix(size_t n, size_t m, T value = 0);
	Matrix(const std::initializer_list<std::initializer_list<T>>& a);
	Matrix(const Matrix& m);
	~Matrix() = default;

	size_t Rows() const;
	size_t Cols() const;

	virtual void Resize(size_t n, size_t m) = 0;
	virtual T& Get(size_t n, size_t m) const = 0;
	virtual T* operator[](size_t index) const = 0;

	bool Square() const;

protected:
	size_t rows = 0;
	size_t cols = 0;
};

template <typename T>
class FlatMatrix: public Matrix<T> {
public:
	FlatMatrix()=default;
	FlatMatrix(size_t n, size_t m, T value = 0);
	FlatMatrix(const std::initializer_list<std::initializer_list<T>>& a);
	FlatMatrix(const FlatMatrix& m);
	~FlatMatrix();

	void Resize(size_t n, size_t m);
	T& Get(size_t n, size_t m) const;
	T* operator[](size_t index) const;

	FlatMatrix<T> operator+(const T& a) const;
	FlatMatrix<T> operator+(const FlatMatrix<T>& m) const;
	FlatMatrix<T> operator-(const T& a) const;
	FlatMatrix<T> operator-(const FlatMatrix<T>& m) const;
	FlatMatrix<T> operator*(const T& a) const;
	FlatMatrix<T> operator*(const FlatMatrix<T>& m) const;

	bool operator==(const FlatMatrix<T>& m) const;
	bool operator!=(const FlatMatrix<T>& m) const;

	FlatMatrix<T> operator= (const FlatMatrix<T>& m);
private:
	T* data = nullptr;
	void reallocate(size_t n, size_t m);
};



template <typename T>
class TableMatrix: public Matrix<T> {
public:
	TableMatrix()=default;
	TableMatrix(size_t n, size_t m, T value = 0);
	TableMatrix(const std::initializer_list<std::initializer_list<T>>& a);
	TableMatrix(const TableMatrix<T>& m);
	~TableMatrix();

	void Resize(size_t n, size_t m);
	T& Get(size_t n, size_t m) const;
	T* operator[](size_t index) const;

	TableMatrix<T> operator+(const T& a) const;
	TableMatrix<T> operator+(const TableMatrix<T>& m) const;
	TableMatrix<T> operator-(const T& a) const;
	TableMatrix<T> operator-(const TableMatrix<T>& m) const;
	TableMatrix<T> operator*(const T& a) const;
	TableMatrix<T> operator*(const TableMatrix<T>& m) const;

	bool operator==(const TableMatrix<T>& m) const;
	bool operator!=(const TableMatrix<T>& m) const;

	TableMatrix<T> operator= (const TableMatrix<T>& m);
private:
	T** data = nullptr;
	void reallocate(size_t n, size_t m);
};


