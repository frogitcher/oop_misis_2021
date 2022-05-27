#pragma once

template <typename T>
class BaseMatrix {
public:
	size_t amount_rows = 0;
	size_t amount_columns = 0;
	BaseMatrix(size_t row, size_t column) {
		amount_rows = row;
		amount_columns = column;
	}
	virtual ~BaseMatrix() = 0;

	virtual void resize(size_t rows, size_t columns) = 0;
	virtual T& get(size_t rows, size_t columns) = 0;

	size_t getAmountRows() const {
		return amount_rows;
	}
	size_t getAmountColumns() const {
		return amount_columns;
	}

	virtual T* operator[](size_t row) const = 0;

	virtual T operator+(const T& other) const = 0;
	virtual T operator-(const T& other) const = 0;
	virtual T operator*(const T& other) const = 0;

	virtual T& operator+=(const T& other) = 0;
	virtual T& operator-=(const T& other) = 0;
	virtual T& operator*=(const T& other) = 0;

	virtual T& operator=(const T& other) = 0;

	virtual bool operator==(const T& other) const = 0;
	virtual bool operator!=(const T& other) const = 0;
};

template <typename T>
class FlatMatrix: public BaseMatrix<T> {
private:
	T* data = nullptr;
public:
	FlatMatrix(size_t rows, size_t columns) {
		this->data = new T[rows * columns];
		this->amount_rows = rows;
		this->amount_columns = columns;
	}
	FlatMatrix(const FlatMatrix<T>& other) {
		delete[] data;
		*this = other;
	}
	FlatMatrix(std::initializer_list<std::initializer_list<T>> list) {
		data = new T[this->amount_rows * this->amount_columns];
		for (int i = 0; i < this->amount_rows; i++) {
			if ((list.begin() + i)->size() != this->amount_columns) {
				throw std::invalid_argument("Impossible to create");
				return;
			}
		}
		for (int i = 0; i < this->amount_rows; i++) {
			std::copy((list.begin() + i)->begin(),
				(list.begin() + i)->begin() + this->amount_columns,
				data + (i * this->amount_columns));
		}
	}
	~FlatMatrix() {
		delete[] data;
	}

	T* operator[](size_t row) const override {
		return data + this->amount_columns * row;
	}

	void resize(size_t rows, size_t columns) override {
		if (rows < 0 || columns < 0) {
			throw std::invalid_argument("Arguments must be positive");
		}
		else {
			T* new_data = new T[rows * columns];
			for (int i = 0; i < rows; i++) {
				std::copy(new_data + i * rows, new_data + i * rows + columns, data = i * this->amount_rows);
			}
			delete[] data;
			data = new_data;
			this->amount_rows = rows;
			this->amount_columns = columns;
		}
	}
	void get(size_t row, size_t column) override {
		if (row < 0 || column < 0 || row >= this->amount_rows || column >= this->amount_columns) {
			throw std::invalid_argument("Arguments outside the value range");
		}
		else {
			return *(data + this->amount_columns * row + column);
		}
	}
	
	FlatMatrix<T> operator+=(const FlatMatrix<T>& other) override {
		if (this->amount_columns != other.amount_columns || this->amount_rows != other.amount_rows) {
			throw std::invalid_argument("Matrix's sizes are not suitable");
		}
		else {
			for (int i = 0; i < this->amount_columns * this->amount_rows; i++) {
				data[i] += other.data[i];
			}
		}
		return *this;
	}
	FlatMatrix<T> operator-=(const FlatMatrix<T>& other) override {
		if (this->amount_columns != other.amount_columns || this->amount_rows != other.amount_rows) {
			throw std::invalid_argument("Matrix's sizes are not suitable");
		}
		else {
			for (int i = 0; i < this->amount_columns * this->amount_rows; i++) {
				data[i] -= other.data[i];
			}
		}
		return *this;
	}
	FlatMatrix<T> operator*=(const FlatMatrix<T>& other) override {
		if (this->amount_columns != other.amount_rows) {
			throw std::invalid_argument("Matrix's sizes are not suitable");
		}
		T* new_data = new T[this->amount_rows * other.amount_columns];
		for (int i = 0; i < this->amount_rows; i++) {
			for (int k = 0; k < this->amount_columns; k++) {
				for (int j = 0; j < other.amount_columns; j++) {
					new_data[i * other.amount_columns + k] +=
						data[i * this->amount_columns + k] * other.data[k * other.amount_row + j];
				}
			}
		}
		delete[] data;
		data = new_data;
		this->amount_columns = other.amount_columns;
		return *this;
	}

	FlatMatrix<T> operator+(const FlatMatrix<T>& other) const override {
		return FlatMatrix(*this) += other;
	}
	FlatMatrix<T> operator-(const FlatMatrix<T>& other) const override {
		return FlatMatrix(*this) -= other;
	}
	FlatMatrix<T> operator*(const FlatMatrix<T>& other) const override {
		return FlatMatrix(*this)*= other;
	}

	FlatMatrix<T> operator=(const FlatMatrix<T>& other) override {
		resize(other.amount_rows, other.amount_columns);
		std::copy(data, data + other.amount_columns * other.amount_rows, other.data);
		this->amount_columns = other.amount_columns;
		this->amount_rows = other.amount_rows;
		return *this;
	}

	bool operator==(const FlatMatrix<T>& other) const override {
		if (this->amount_columns == other.amount_columns &&
			this->amount_rows == other.amount_rows &&
			std::equal(data,
				data + this->amount_columns * this->amount_rows,
				other.data,
				other.data + other.amount_columns * other.amount_rows)) {
			return true;
		}
		return false;
	}
	bool operator!=(const FlatMatrix<T>& other) const override {
		return !(*this == other);
	}
};

template <typename T>
class TableMatrix: public BaseMatrix<T> {
private:
	T** data = nullptr;
public:
	TableMatrix(size_t rows, size_t columns) {
		data = new T* [rows];
		for (int i = 0; i < rows; i++) {
			data[i] = new T[columns];
		}
	}
	TableMatrix(const TableMatrix<T>& other) {
		delete[] data;
		*this = other;
	}
	TableMatrix(std::initializer_list<std::initializer_list<T>> list) {
		for (int i = 0; i < this->amount_rows; i++) {
			if ((list.begin() + i)->size() != this->amount_columns) {
				throw std::invalid_argument("Impossible to create");
				return;
			}
		}
		data = new T* [this];
		for (int i = 0; i < this->amount_rows; i++) {
			data[i] = new T[this->amount_columns];
			std::copy((list.begin() + i)->begin(), (list.begin() + i)->end(), data[i]);
		}
	}
	~TableMatrix() {
		for (int i = 0; i < this->amount_rows; i++) {
			delete[] data[i];
		}
		delete[] data;
	}

	T* operator[](size_t row) const override {
		return data[row];
	}

	void resize(size_t rows, size_t columns) override {
		if (rows < 0 || columns < 0) {
			throw std::invalid_argument("Arguments must be positive");
		}
		else {
			T** new_data = new T* [rows];
			for (int i = 0; i < rows; i++) {
				new_data[i] = new T* [columns];
				std::copy(new_data[i], new_data[i] + columns, data[i]);
			}
			for (int i = 0; i < this->amount_rows; i++) {
				delete[] data[i];
			}
			delete[] data;
			data = new_data;
			this->amount_rows = rows;
			this->amount_columns = columns;
		}
	}
	void get(size_t row, size_t column) override {
		if (row < 0 || column < 0 || row >= this->amount_rows || column >= this->amount_columns) {
			throw std::invalid_argument("Arguments outside the value range");
		}
		else {
			return data[row][column];
		}
	}

	TableMatrix<T> operator+=(const TableMatrix<T>& other) override {
		if (this->amount_columns != other.amount_columns || this->amount_rows != other.amount_rows) {
			throw std::invalid_argument("Matrix's sizes are not suitable");
		}
		else {
			for (int i = 0; i < other.amount_rows; i++) {
				for (int j = 0; j < other.amount_columns; j++) {
					data += other.data[i][j];
				}
			}
		}
		return *this;
	}
	TableMatrix<T> operator-=(const TableMatrix<T>& other) override {
		if (this->amount_columns != other.amount_columns || this->amount_rows != other.amount_rows) {
			throw std::invalid_argument("Matrix's sizes are not suitable");
		}
		else {
			for (int i = 0; i < other.amount_rows; i++) {
				for (int j = 0; j < other.amount_columns; j++) {
					data -= other.data[i][j];
				}
			}
		}
		return *this;
	}
	TableMatrix<T> operator*=(const TableMatrix<T>& other) override {
		if (this->amount_columns != other.amount_rows) {
			throw std::invalid_argument("Matrix's sizes are not suitable");
		}
		T* new_data = new T[this->amount_rows * other.amount_columns];
		for (int i = 0; i < this->amount_rows; i++) {
			for (int k = 0; k < this->amount_columns; k++) {
				for (int j = 0; j < other.amount_columns; j++) {
					new_data[i][k] += data[i][k] * other.data[k][j];
				}
			}
			delete[] data[i];
		}
		delete[] data;
		data = new_data;
		this->amount_columns = other.amount_columns;
		return *this;
	}

	TableMatrix<T> operator+(const TableMatrix<T>& other) const override {
		return TableMatrix(*this) += other;
	}
	TableMatrix<T> operator-(const TableMatrix<T>& other) const override {
		return TableMatrix(*this) -= other;
	}
	TableMatrix<T> operator*(const TableMatrix<T>& other) const override {
		return TableMatrix(*this) *= other;
	}

	TableMatrix<T> operator=(const TableMatrix<T>& other) override {
		resize(other.amount_rows, other.amount_columns);
		for (int i = 0; i < other.amount_rows; i++) {
			std::copy(data[i], data[i] + other.amount_columns, other.data[i]);
		}
		this->amount_columns = other.amount_columns;
		this->amount_rows = other.amount_rows;
		return *this;
	}

	bool operator==(const TableMatrix<T>& other) const override {
		if (this->amount_columns == other.amount_columns &&
			this->amount_rows == other.amount_rows) {
			for (int i = 0; i < other.amount_rows; i++) {
				if (std::equal(data[i],
					data[i] + this->amount_columns,
					other.data[i],
					other.data[i] + other.amount_columns) == false) {
					return false;
				}
				return true;
			}
		}
		return false;
	}
	bool operator!=(const TableMatrix<T>& other) const override {
		return !(*this == other);
	}
};