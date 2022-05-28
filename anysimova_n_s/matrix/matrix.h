#pragma once
#include <cstdint>

template <typename T>
class BaseMatrix {
public:
	BaseMatrix(int64_t row = 0, int64_t col = 0);
	~BaseMatrix();

	virtual T& get(int64_t r, int64_t c) const = 0;
	virtual void resize(int64_t r, int64_t c, const T filler = T(0)) = 0;
	virtual void diag(int64_t r, const T filler) = 0;

	bool IsSquare() const;
	int64_t rows() const;
	int64_t colums() const;
protected:
	int64_t row_ = 0;
	int64_t col_ = 0;
};

template <typename T>
std::ostream& operator<<(std::ostream& ostrm, BaseMatrix<T>& rhs) {
	for (int i = 0; i < rhs.rows(); i++) {
		for (int j = 0; j < rhs.colums(); j++) {
			ostrm << rhs.get(i, j) << " ";
		}
		ostrm << std::endl;
	}
	return ostrm;
}

template <typename T>
BaseMatrix<T>::BaseMatrix(int64_t row = 0, int64_t col = 0)
	: row_(row)
	, col_(col) {}

template <typename T>
BaseMatrix<T>::~BaseMatrix() = default;

template <typename T>
bool BaseMatrix<T>::IsSquare() const {
	return row_ == col_;
}

template <typename T>
int64_t BaseMatrix<T>::rows() const {
	return row_;
}

template <typename T>
int64_t BaseMatrix<T>::colums() const {
	return col_;
}