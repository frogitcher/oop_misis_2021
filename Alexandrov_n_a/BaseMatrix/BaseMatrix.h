#include <initializer_list>
template <typename T>
class BaseMatrix {
public:
	virtual void Resize(size_t rows, size_t cols) = 0;
	virtual T& Get(size_t rows, size_t cols) const = 0;
	virtual T* operator[] (size_t r) const = 0;
	~BaseMatrix() = default;
	BaseMatrix(size_t row, size_t col);
	BaseMatrix(const BaseMatrix<T>& other);
	BaseMatrix(std::initializer_list<std::initializer_list<T>> m);
	size_t Row_() const;
	size_t Col_() const;
protected:
	size_t Col = 0;
	size_t Row = 0;
};






template <typename T>
class FlatMatrix : public BaseMatrix<T> {
public:
	FlatMatrix(size_t row, size_t col);
	FlatMatrix(const FlatMatrix<T>& other);
	FlatMatrix(std::initializer_list<std::initializer_list<T>> m);
	~FlatMatrix();
	FlatMatrix<T> operator+ (const FlatMatrix<T>& m) const;
	FlatMatrix<T> operator- (const FlatMatrix<T>& m) const;
	void operator= (const FlatMatrix<T>& m);
	FlatMatrix<T> operator+ (const T& value) const;
	FlatMatrix<T> operator- (const T& value) const;
	FlatMatrix<T> operator* (const FlatMatrix<T>& m) const;
	FlatMatrix<T> operator* (const T& m) const;
	T* operator[](size_t index) const override;
	bool operator== (const FlatMatrix<T>& m) const;
	bool operator!= (const FlatMatrix<T>& m) const;
	T& Get(size_t ind_row, size_t ind_col) const override;
	void Resize(size_t rows, size_t cols) override;
private:
	T* data = nullptr;
};
template<typename T>
FlatMatrix<T> operator+(const T& value, const FlatMatrix<T>& other) {
	return other + value;
}
template<typename T>
FlatMatrix<T> operator-(const T& value, const FlatMatrix<T>& other) {
	return other - value;
}
template<typename T>
FlatMatrix<T> operator*(const T& value, const FlatMatrix<T>& other) {
	return other * value;
}






template <typename T>
class ListMatrix : public BaseMatrix<T> {
public:
	ListMatrix(size_t row, size_t col);
	ListMatrix(const ListMatrix<T>& other);
	ListMatrix(std::initializer_list<std::initializer_list<T>> m);
	~ListMatrix();
	ListMatrix<T> operator+ (const ListMatrix<T>& m) const;
	ListMatrix<T> operator- (const ListMatrix<T>& m) const;
	void operator= (const ListMatrix<T>& m);
	ListMatrix<T> operator+ (const T& value) const;
	ListMatrix<T> operator- (const T& value) const;
	ListMatrix<T> operator* (const ListMatrix<T>& m) const;
	ListMatrix<T> operator* (const T& m) const;
	T* operator[](size_t index) const override;
	bool operator== (const ListMatrix<T>& m) const;
	bool operator!= (const ListMatrix<T>& m) const;
	T& Get(size_t rows, size_t cols) const override;
	void Resize(size_t rows, size_t cols) override;
private:
	T** data = nullptr;
};
template<typename T>
ListMatrix<T> operator+(const T& value, const ListMatrix<T>& other) {
	return other + value;
}
template<typename T>
ListMatrix<T> operator-(const T& value, const ListMatrix<T>& other) {
	return other - value;
}
template<typename T>
ListMatrix<T> operator*(const T& value, const ListMatrix<T>& other) {
	return other * value;
}







template<typename T>
size_t BaseMatrix<T>::Row_() const {
	return Row;
}
template<typename T>
size_t BaseMatrix<T>::Col_() const {
	return Col;
}
template <typename T>
BaseMatrix<T>::BaseMatrix(size_t row, size_t col) {
	Col = col;
	Row = row;
}
template <typename T>
BaseMatrix<T>::BaseMatrix(std::initializer_list<std::initializer_list<T>> m) {
	Row = m.size();
	Col = m.begin()->size();
}
template <typename T>
BaseMatrix<T>::BaseMatrix(const BaseMatrix<T>& other) {
	Row = other.Row;
	Col = other.Col;
}








template<typename T>
void FlatMatrix<T>::Resize(size_t rows, size_t cols) {
	T* returned_data = new T[rows * cols];
	std::fill(returned_data, returned_data + cols * rows, 0);
	for (size_t i = 0; i < std::min(rows, Row); ++i) {
		for (size_t j = 0; j < std::min(cols, Col); ++j) {
			returned_data[i * cols + j] = data[i * Col + j];
		}
	}
	delete[] data;
	data = returned_data;
	Row = rows;
	Col = cols;
}
template<typename T>
T& FlatMatrix<T>::Get(size_t ind_row, size_t ind_col) const {
	if (ind_row > Row - 1 || ind_col > Col - 1) {
		throw "Out of range";
	}
	return data[ind_col * Col + ind_row];
}
template <typename T>
FlatMatrix<T>::FlatMatrix(size_t row, size_t col) : BaseMatrix<T>(row, col){
	/*Col = col;
	Row = row;*/
	data = new T[col * row];
	std::fill(data, data + Col * Row, 0);
}
template <typename T>
T* FlatMatrix<T>::operator[](size_t index) const {
	if (index > Row - 1) {
		throw "Out of range";
	}
	else {
		return (data + (Col * index));
	}
}
template<typename T>
FlatMatrix<T>::~FlatMatrix() {
	delete[] data;
}
template <typename T>
FlatMatrix<T>::FlatMatrix(const FlatMatrix<T>& other) : BaseMatrix<T>(other) {
	data = new T[Row * Col];
	for (int i = 0; i < Row * Col; i++) {
		data[i] = other.data[i];
	}
}
template <typename T>
FlatMatrix<T>::FlatMatrix(std::initializer_list<std::initializer_list<T>> m) : BaseMatrix<T>(m){
	data = new T[Row * Col];
	int k = 0;
	for (auto i : m) {
		int kk = 0;
		for (auto j : i) {
			data[kk + k] = j;
			kk++;
		}
		k += Col;
	}
}
template<typename T>
FlatMatrix<T> FlatMatrix<T>::operator+ (const FlatMatrix<T>& m) const {
	if (Row != m.Row || Col != m.Col) {
		throw "different size!";
	}
	FlatMatrix<T> returned_matrix(m);
	for (int i = 0; i < Row * Col; i++) {
		returned_matrix.data[i] += data[i];
	}
	return returned_matrix;
}
template<typename T>
FlatMatrix<T> FlatMatrix<T>::operator- (const FlatMatrix<T>& m) const {
	if (Row != m.Row || Col != m.Col) {
		throw "different size!";
	}
	FlatMatrix<T> returned_matrix(*this);
	for (int i = 0; i < Row * Col; i++) {
		returned_matrix.data[i] -= m.data[i];
	}
	return returned_matrix;
}
template<typename T>
FlatMatrix<T> FlatMatrix<T>:: operator+ (const T& value) const {
	if (Row != Col) {
		throw "Wrong size!";
	}
	FlatMatrix<T> returned_matrix(*this);
	int k = 0;
	for (int i = 0; i < Row * Col; i += Row) {
		returned_matrix.data[i + k] += value;
		k += 1;
	}
	return returned_matrix;
}
template<typename T>
FlatMatrix<T> FlatMatrix<T>:: operator- (const T& value) const {
	if (Row != Col) {
		throw "Wrong size!";
	}
	FlatMatrix<T> returned_matrix(*this);
	int k = 0;
	for (int i = 0; i < Row * Col; i += Row) {
		returned_matrix.data[i + k] -= value;
		k += 1;
	}
	return returned_matrix;
}
template<typename T>
void FlatMatrix<T>::operator= (const FlatMatrix<T>& m) {
	if (data != nullptr) {
		delete[] data;
	}
	Row = m.Row;
	Col = m.Col;
	data = new T[Row * Col];
	for (int i = 0; i < Row * Col; i++) {
		data[i] = m.data[i];
	}
}
template<typename T>
FlatMatrix<T> FlatMatrix<T>::operator* (const FlatMatrix<T>& m) const {
	if (Col != m.Row) {
		throw "Wrong size!";
	}
	FlatMatrix<T> returned_matrix(Row, m.Col);
	int k = 0;
	for (int i = 0; i < Row * m.Col; i++) {
		for (int j = 0; j < Col; j++) {
			int time_per = data[j + Col * k] * m.data[i % m.Col + j * m.Col];
			returned_matrix.data[i] += time_per;
		}
		if ((i % m.Col == m.Col - 1) && i > 0) {
			k += 1;
		}
	}
	return returned_matrix;
}
template<typename T>
FlatMatrix<T> FlatMatrix<T>::operator* (const T& m) const {
	FlatMatrix<T> returned_matrix(*this);
	for (int i = 0; i < Row * Col; i++) {
		returned_matrix.data[i] *= m;
	}
	return returned_matrix;
}
template<typename T>
bool FlatMatrix<T>::operator== (const FlatMatrix<T>& m) const {
	int flag = 0;
	if (Row != m.Row || Col != m.Col) {
		return false;
	}
	for (int i = 0; i < Row * Col; i++) {
		if (data[i] != m.data[i]) {
			flag = 1;
			break;
		}
	}
	if (flag == 0) {
		return true;
	}
	if (flag != 0) {
		return false;
	}
}
template<typename T>
bool FlatMatrix<T>::operator!= (const FlatMatrix<T>& m) const {
	return !(*this == m);
}






template<typename T>
void ListMatrix<T>::Resize(size_t rows, size_t cols) {
	ListMatrix<T> returned_matrix(*this);
	for (int i = 0; i < Row; i++) {
		delete[] data[i];
	}
	delete[] data;
	data = new T*[rows];
	for (int i = 0; i < rows; i++) {	
		data[i] = new T[cols];
		for (int j = 0; j < cols; j++) {
			data[i][j] = 0;
		}
	}
	for (int i = 0; i < Row; i++) {
		for (int j = 0; j < Col; j++) {
			data[i][j] = returned_matrix[i][j];
		}
	}
	Col = cols;
	Row = rows;
}
template<typename T>
bool ListMatrix<T>::operator!= (const ListMatrix<T>& m) const {
	return !(*this == m);
}
template<typename T>
ListMatrix<T>::ListMatrix(std::initializer_list<std::initializer_list<T>> m) : BaseMatrix<T>(m){
	data = new T * [Row];
	int k = 0;
	for (auto i : m) {
		int kk = 0;
		data[k] = new T[Col];
		for (auto j : i) {
			data[k][kk] = j;
			kk++;
		}
		k++;
	}
}
template<typename T>
T* ListMatrix<T>::operator[] (size_t index) const {
	if (index > Row - 1) {
		throw "Out of range";
	}
	else {
		return data[index];
	}
}
template<typename T>
T& ListMatrix<T>::Get(size_t ind_row, size_t ind_col) const {
	if (ind_row > Row - 1 || ind_col > Col - 1) {
		throw "Out of range";
	}
	return data[ind_row][ind_col];
}
template<typename T>
ListMatrix<T>::ListMatrix(size_t row, size_t col) : BaseMatrix<T>( row, col) {
	data = new T * [row];
	for (int i = 0; i < row; i++) {
		data[i] = new T[col];
		for (int j = 0; j < col; j++) {
			data[i][j] = 0;
		}
	}
}
template<typename T>
ListMatrix<T> ListMatrix<T>::operator+ (const ListMatrix<T>& m) const {
	if (Row != m.Row || Col != m.Col) {
		throw "different size!";
	}
	ListMatrix<T> returned_matrix(m);
	for (int i = 0; i < Row; i++) {
		for (int j = 0; j < Col; j++) {
			returned_matrix[i][j] += data[i][j];
		}
	}
	return returned_matrix;
}
template<typename T>
ListMatrix<T> ListMatrix<T>::operator- (const ListMatrix<T>& m) const {
	if (Row != m.Row || Col != m.Col) {
		throw "different size!";
	}
	ListMatrix<T> returned_matrix(m);
	for (int i = 0; i < Row; i++) {
		for (int j = 0; j < Col; j++) {
			returned_matrix[i][j] = data[i][j] - m[i][j];
		}
	}
	return returned_matrix;
}
template<typename T>
void ListMatrix<T>::operator= (const ListMatrix<T>& m) {
	for (int i = 0; i < Row; i++) {
		delete[] data[i];
	}
	delete[] data;
	Row = m.Row;
	Col = m.Col;
	data = new T * [Row];
	for (int i = 0; i < Row; i++) {
		data[i] = new T[Col];
		for (int j = 0; j < Col; j++) {
			data[i][j] = m[i][j];
		}
	}
}
template<typename T>
ListMatrix<T>::ListMatrix(const ListMatrix<T>& other) : BaseMatrix<T>(other) {
	data = new T * [Row];
	for (int i = 0; i < Row; i++) {
		data[i] = new T[Col];
		for (int j = 0; j < Col; j++) {
			data[i][j] = other[i][j];
		}
	}
}
template<typename T>
ListMatrix<T> ListMatrix<T>:: operator+ (const T& value) const {
	if (Row != Col) {
		throw "Wrong size!";
	}
	ListMatrix<T> returned_matrix(*this);
	for (int i = 0; i < Row; i++) {
		returned_matrix[i][i] += value;
	}
	return returned_matrix;
}
template<typename T>
ListMatrix<T> ListMatrix<T>::operator- (const T& value) const {
	if (Row != Col) {
		throw "Wrong size!";
	}
	ListMatrix<T> returned_matrix(*this);
	for (int i = 0; i < Row; i++) {
		returned_matrix[i][i] -= value;
	}
	return returned_matrix;
}
template<typename T>
ListMatrix<T> ListMatrix<T>::operator* (const ListMatrix<T>& m) const {
	if (Col != m.Row) {
		throw "Wrong size!";
	}
	ListMatrix<T> returned_matrix(Row, m.Col);
	for (int i = 0; i < returned_matrix.Row; i++) {
		for (int j = 0; j < returned_matrix.Col; j++) {
			for (int k = 0; k < Col; k++) {
				returned_matrix[i][j] += data[i][k] * m[k][j];
			}
		}
	}
	return returned_matrix;
}
template<typename T>
ListMatrix<T> ListMatrix<T>::operator* (const T& m) const {
	ListMatrix<T> returned_matrix(*this);
	for (int i = 0; i < Row; i++) {
		for (int j = 0; j < Col; j++) {
			returned_matrix[i][j] *= m;
		}
	}
	return returned_matrix;
}
template<typename T>
ListMatrix<T>::~ListMatrix() {
	for (int i = 0; i < Row; i++) {
		delete[] data[i];
	}
	delete[] data;
}
template<typename T>
bool ListMatrix<T>::operator== (const ListMatrix<T>& m) const {
	if (Row != m.Row || Col != m.Col) {
		return false;
	}
	int flag = 0;
	for (int i = 0; i < Row; i++) {
		for (int j = 0; j < Col; j++) {
			if (m[i][j] != data[i][j]) {
				flag = 1;
				break;
			}
		}
	}
	if (flag == 0) return true;
	if (flag != 0) return false;
}