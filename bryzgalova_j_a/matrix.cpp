template <typename T>
Matrix<T>::Matrix(size_t n, size_t m, T value) {
	line= n;
	column = m;
}

template <typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>>& a) {
	for (auto i : a) {
		if (i.size() != a.begin()->size()) {
			throw std::invalid_argument("Rows are not equal");
		}
	}
	line= a.size();
	column= a.begin()->size();
}

template <typename T>
size_t Matrix<T>::Line() const {
	return line;
}

template <typename T>
size_t Matrix<T>::Column() const {
	return column;
}

template <typename T>
Matrix<T>::Matrix(const Matrix& m) {
	line = m.Line();
	column = m.Column();
}

template <typename T>
bool Matrix<T>::Square() const {
	return (line == column);
}

template <typename T>
void TableMatrix<T>::reallocate(size_t n, size_t m) {
	T** new_data = new T* [n];
	for (int i=0; i<Matrix<T>::line; i++) {
		new_data[i] = new T[m];
		std::copy(data[i], data[i]+Matrix<T>::column, new_data[i]);
	}
	for (int i=Matrix<T>::line; i<n; i++) {
        new_data[i] = new T[m];
	}
	delete[]data;
	data = new_data;
}

template <typename T>
TableMatrix<T>::TableMatrix(size_t n, size_t m, T value): Matrix<T>(n, m) {
	data = new T* [n];
	for (int i=0; i<Matrix<T>::column; i++) {
		data[i] = new T[m];
		std::fill(data[i], data[i]+Matrix<T>::column, value);
	}
}

template <typename T>
TableMatrix<T>::TableMatrix(const std::initializer_list<std::initializer_list<T>>& a): Matrix<T>(a) {
	data = new T* [Matrix<T>::line];
	int ind_i = 0;
	for (auto i : a) {
		data[ind_i] = new T[Matrix<T>::column];
		std::copy(i.begin(), i.end(), data[ind_i]);
		++ind_i;
	}
}

template <typename T>
TableMatrix<T>::TableMatrix(const TableMatrix<T>& m): Matrix<T>(m.Matrix<T>::Line(), m.Matrix<T>::Column()) {
	data = new T* [m.Matrix<T>::Line()];
	for (int i=0; i<Matrix<T>::line; i++) {
		data[i] = new T[m.Matrix<T>::Column()];
		std::copy(m.data[i], m.data[i]+m.Matrix<T>::Column(), data[i]);
	}
}

template <typename T>
TableMatrix<T>::~TableMatrix() {
	for (int i=0; i<Matrix<T>::line; i++) {
		delete[]data[i];
	}
	delete[]data;
}

template <typename T>
void TableMatrix<T>::Resize(size_t n, size_t m) {
	if (n>Matrix<T>::line && m>Matrix<T>::column) {
        reallocate(n, m);
        for (int i=0; i<Matrix<T>::line; i++) {
			std::fill(data[i]+Matrix<T>::column, data[i]+m, 0);
		}
		for (int i=Matrix<T>::line; i<n; i++) {
			std::fill(data[i], data[i]+m, 0);
		}

		BaseMatrix<T>::line=n;
        BaseMatrix<T>::column=m;
        return;
	}

	if (n>Matrix<T>::line) {
		reallocate(n, m);
		for (int i=Matrix<T>::line; i<n; i++) {
			std::fill(data[i], data[i]+Matrix<T>::column, 0);
		}
	}

	if (m>Matrix<T>::column) {
		reallocate(n, m);
		for (int i=0; i<n; i++) {
			std::fill(data[i]+Matrix<T>::column, data[i]+m, 0);
		}
	}

	Matrix<T>::line=n;
	Matrix<T>::column=m;
}

template <typename T>
T& TableMatrix<T>::Get(size_t n, size_t m) const {
	if (n>= Matrix<T>::line || m >= Matrix<T>::column) {
		throw std::invalid_argument("Index out of range!");
	}
	return data[n][m];
}

template <typename T>
T* TableMatrix<T>::operator[](size_t ind) const {
	if (ind >= Matrix<T>::line) {
		throw std::invalid_argument("Index out of range!");
	}
	return data[ind];
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator+(const T& a) const {
	if (Matrix<T>::Square()) {
		TableMatrix<T> matrix(*this);
		for (int i=0; i<Matrix<T>::line; i++) {
			matrix.data[i][i]+=a;
		}
		return matrix;
	}
	else {
		throw std::invalid_argument("Not square!");
	}
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator-(const T& a) const {
	if (Matrix<T>::Square()) {
		TableMatrix<T> matrix(*this);
		for (int i=0; i<Matrix<T>::line; i++) {
			matrix.data[i][i]-=a;
		}
		return matrix;
	}
	else {
		throw std::invalid_argument("Not square!");
	}
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator*(const T& a) const {
	TableMatrix<T> matrix(*this);
	for (int i=0; i<Matrix<T>::line; i++) {
		for (int j=0; j<Matrix<T>::column; j++) {
			matrix.data[i][j]*=a;
		}
	}
	return matrix;
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator+(const TableMatrix<T>& m) const {
	if (Matrix<T>::line == m.Matrix<T>::Line() && Matrix<T>::column == m.Matrix<T>::Column()) {
		TableMatrix<T> matrix(m);
		for (int i=0; i<Matrix<T>::line; i++) {
			for (int j=0; j<Matrix<T>::column; j++) {
				matrix.data[i][j]+=data[i][j];
			}
		}
		return matrix;
	}
	else {
		throw std::invalid_argument("Operation isn't permitted !");
	}
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator-(const TableMatrix<T>& m) const {
	if (Matrix<T>::line == m.Matrix<T>::Line() && Matrix<T>::column == m.BaseMatrix<T>::Column()) {
		TableMatrix<T> matrix(m);
		for (int i=0; i<Matrix<T>::line; i++) {
			for (int j=0; j<Matrix<T>::column; j++) {
				matrix.data[i][j]-=data[i][j];
			}
		}
		return matrix;
	}
	else {
		throw std::invalid_argument("Operation isn't permitted !");
	}
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator*(const TableMatrix<T>& rhs) const{
    if (Matrix<T>::column != rhs.Matrix<T>::Line()){
        throw std::invalid_argument("Operation isn't permitted !");
    } else{
        TableMatrix<T> answer(Matrix<T>::line, rhs.Matrix<T>::Column());
        for (int i=0; i < answer.Matrix<T>::Line(); ++i){
            for (int j=0; j < answer.Matrix<T>::Column(); ++j){
                size_t index = 0;
                while (index < Matrix<T>::column){
                    answer[i][j] += (data[i][index] * rhs.data[index][j]);
                    ++index;
                }
            }
        }
        return answer;
    }
}

template <typename T>
bool TableMatrix<T>::operator==(const TableMatrix<T>& m) const {
	if (Matrix<T>::line!=m.Matrix<T>::Line() || Matrix<T>::column!=m.Matrix<T>::Column()) {
		return false;
	}
	for (int i=0; i<Matrix<T>::line; i++) {
		if (! std::equal(data[i], data[i]+Matrix<T>::column, m.data[i], m.data[i]+Matrix<T>::column)) {
			return false;
		}
	}
	return true;
}

template <typename T>
bool TableMatrix<T>::operator!=(const TableMatrix<T>& m) const {
	return !(*this==m);
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator= (const TableMatrix<T>& m) {
	if (m.Matrix<T>::Line()>Matrix<T>::line || m.Matrix<T>::Column()>Matrix<T>::column) {
		reallocate(m.Matrix<T>::Line(), m.Matrix<T>::Column());
	}
	Matrix<T>::line=m.Matrix<T>::Line();
	Matrix<T>::column=m.Matrix<T>::Column();

	for (int i=0; i<Matrix<T>::column; i++) {
		std::copy(m.data[i], m.data[i]+m.Matrix<T>::Column(), data[i]);
	}
	return *this;

}

template <typename T>
void FlatMatrix<T>::reallocate(size_t n, size_t m) {
	T* new_data = new T [n*m];
	for (int i=0; i<Matrix<T>::line; i++) {
		std::copy(data+i*Matrix<T>::column, data+(i+1)*Matrix<T>::column, new_data+i*m);
	}
	delete[]data;
	data = new_data;
}

template <typename T>
Matrix<T>::Matrix(size_t n, size_t m, T value): Matrix<T>(n, m) {
	data = new T[Matrix<T>::line*Matrix<T>::column];
	std::fill(data, data+Matrix<T>::line*Matrix<T>::column, value);
}

template <typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>>& a): Matrix<T>(a) {
	data = new T[Matrix<T>::line*Matrix<T>::column];
	int indi=0;
	for (auto i : A) {
        int indj = 0;
		for (auto j : i) {
			data[indi*Matrix<T>::column+indj]=j;
            ++indj;
		}
		++indi;
	}
}

template <typename T>
FlatMatrix<T>::FlatMatrix(const FlatMatrix& m): Matrix<T>(m.Line(), m.Column()){
	data = new T[Matrix<T>::line*Matrix<T>::column];
	for (int i=0; i<Matrix<T>::line; i++) {
		for (int j=0; j<Matrix<T>::column; j++) {
			data[i*Matrix<T>::column+j]=m.Get(i, j);
		}
	}
}

template <typename T>
FlatMatrix<T>::~FlatMatrix() {
	delete[]data;
}

template <typename T>
void FlatMatrix<T>::Resize(size_t n, size_t m) {
	if (n>Matrix<T>::line && m>Matrix<T>::column) {
        reallocate(n, m);
        for (int i=0; i<Matrix<T>::line; i++) {
			std::fill(data+i*m+Matrix<T>::column, data+(i+1)*m, 0);
		}
		std::fill(data+Matrix<T>::line*m, data+m*n, 0);
		Matrix<T>::line = n;
        Matrix<T>::column = m;
	}
	else {
        if (n>Matrix<T>::line) {
            reallocate(n, m);
            std::fill(data+Matrix<T>::line*Matrix<T>::column, data+m*n, 0);
        }
        if (m>Matrix<T>::column) {
            reallocate(n, m);
            for (int i=0; i<n; i++) {
                std::fill(data+i*m+Matrix<T>::column, data+(i+1)*m, 0);
            }
        }
        Matrix<T>::line = n;
        Matrix<T>::column = m;
	}

}

template <typename T>
T& FlatMatrix<T>::Get(size_t n, size_t m) const {
	if (n>= Matrix<T>::line|| m >= Matrix<T>::column) {
		throw std::invalid_argument("Index out of range!");
	}
	return data[n*Matrix<T>::column+m];
}

template <typename T>
T* FlatMatrix<T>::operator[](size_t index) const {
	if (index >= Matrix<T>::line) {
		throw std::invalid_argument("Index out of range!");
	}
	return data+index*Matrix<T>::column;
}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator+(const T& a) const {
	if (Matrix<T>::Square()) {
		FlatMatrix<T> matrix(*this);
		for (int i=0; i<Matrix<T>::line; i++) {
			for (int j=0; j<Matrix<T>::column; j++) {
				if (i==j) {
					matrix.data[i*Matrix<T>::column+j]+=a;
				}
			}
		}
		return matrix;
	}
	else {
		throw std::invalid_argument("Not square!");
	}



}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator+(const FlatMatrix<T>& m) const {
	if (Matrix<T>::column==m.Column() && Matrix<T>::line==m.line()) {
		FlatMatrix<T> matrix(m);
		for (int i=0; i<Matrix<T>::column*Matrix<T>::line; i++) {
			matrix.data[i]+=data[i];
		}
		return matrix;
	}
	else {
		throw std::invalid_argument("Operation isn't permitted !");
	}

}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator-(const T& a) const {
	if (Matrix<T>::column==m.Column() && Matrix<T>::line==m.Line()) {
		FlatMatrix<T> matrix(*this);
		for (int i=0; i<Matrix<T>::Line(); i++) {
			for (int j=0; j<Matrix<T>::Column(); j++) {
				if (i==j) {
					matrix.data[i*Matrix<T>::Column()+j]-=a;
				}
			}
		}
        return matrix;
	}
	else {
		throw std::invalid_argument("Operation is not permission");
	}

}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator-(const FlatMatrix<T>& m) const {
	if (Matrix<T>::Column()==m.Matrix<T>::Column() && Matrix<T>::Line()==m.Matrix<T>::Line()) {
		FlatMatrix<T> matrix(m);
		for (int i=0; i<Matrix<T>::Column()*Matrix<T>::Line(); i++) {
			matrix.data[i]-=data[i];
		}
		return matrix;
	}
	else {
		throw std::invalid_argument("Operation isn't permitted !");
	}

}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator*(const T& a) const {
	FlatMatrix<T> matrix(*this);
	for (int i=0; i<Matrix<T>::line*Matrix<T>::column; i++) {
		matrix.data[i]*=a;
	}
	return matrix;
}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator*(const FlatMatrix<T>& m) const {
	if (Matrix<T>::column==m.Matrix<T>::Line()) {
		FlatMatrix<T> matrix(Matrix<T>::Line(), m.Matrix<T>::Column());
		for (int i=0; i<Matrix<T>::line; i++) {
			for (int j=0; j<m.Matrix<T>::Column(); j++) {
				T sum = 0;
				for (int index=0; index< Matrix<T>::column; i++) {
					sum+=data[i*Matrix<T>::column+index]*m.data[index*m.Matrix<T>::column+j];
				}
				matrix.data[i*m.Matrix<T>::Colunm()+j]=sum;
			}
		}
		return matrix;
	}
	else {
		throw std::invalid_argument("Operation isn't permitted !");
	}

}

template <typename T>
bool FlatMatrix<T>::operator==(const FlatMatrix<T>& m) const {
	if (Matrix<T>::line!=m.Matrix<T>::Line() || Matrix<T>::column!=m.BaseMatrix<T>::Column()) {
		return false;
	}
	return std::equal(data, data+Matrix<T>::column*Matrix<T>::line, m.data, m.data+m.Matrix<T>::Column()*m.Matrix<T>::Line());
}

template <typename T>
bool FlatMatrix<T>::operator!=(const FlatMatrix<T>& m) const {
	return !(*this==m);
}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator=(const FlatMatrix<T>& m) {
	Resize(m.Matrix<T>::line, m.Matrix<T>::column);
	for (int i=0; i<Matrix<T>::line*Matrix<T>::column; i++) {
        data[i] = m.data[i];
	}
	return *this;
}