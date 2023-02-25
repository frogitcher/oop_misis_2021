template <typename T>
Matrix<T>::Matrix(size_t n, size_t m, T value) {
	rows = n;
	cols = m;
}

template <typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>>& a) {
	for (auto i : a) {
		if (i.size() != a.begin()->size()) {
			throw std::invalid_argument("Rows are not equal");
		}
	}
	rows = a.size();
	cols = a.begin()->size();
}

template <typename T>
size_t Matrix<T>::Rows() const {
	return rows;
}

template <typename T>
size_t Matrix<T>::Cols() const {
	return cols;
}

template <typename T>
Matrix<T>::Matrix(const Matrix& m) {
	rows = m.Rows();
	cols = m.Cols();
}

template <typename T>
bool Matrix<T>::Square() const {
	return (rows == cols);
}

template <typename T>
void TableMatrix<T>::reallocate(size_t n, size_t m) {
	T** new_data = new T* [n];
	for (int i=0; i<Matrix<T>::rows; i++) {
		new_data[i] = new T[m];
		std::copy(data[i], data[i]+Matrix<T>::cols, new_data[i]);
	}
	for (int i=Matrix<T>::rows; i<n; i++) {
        new_data[i] = new T[m];
	}
	delete[]data;
	data = new_data;
}

template <typename T>
TableMatrix<T>::TableMatrix(size_t n, size_t m, T value): Matrix<T>(n, m) {
	data = new T* [n];
	for (int i=0; i<Matrix<T>::cols; i++) {
		data[i] = new T[m];
		std::fill(data[i], data[i]+Matrix<T>::cols, value);
	}
}

template <typename T>
TableMatrix<T>::TableMatrix(const std::initializer_list<std::initializer_list<T>>& a): Matrix<T>(a) {
	data = new T* [Matrix<T>::rows];
	int ind_i = 0;
	for (auto i : a) {
		data[ind_i] = new T[Matrix<T>::cols];
		std::copy(i.begin(), i.end(), data[ind_i]);
		++ind_i;
	}
}

template <typename T>
TableMatrix<T>::TableMatrix(const TableMatrix<T>& m): Matrix<T>(m.Matrix<T>::Rows(), m.Matrix<T>::Cols()) {
	data = new T* [m.Matrix<T>::Rows()];
	for (int i=0; i<Matrix<T>::rows; i++) {
		data[i] = new T[m.Matrix<T>::Cols()];
		std::copy(m.data[i], m.data[i]+m.Matrix<T>::Cols(), data[i]);
	}
}

template <typename T>
TableMatrix<T>::~TableMatrix() {
	for (int i=0; i<Matrix<T>::rows; i++) {
		delete[]data[i];
	}
	delete[]data;
}

template <typename T>
void TableMatrix<T>::Resize(size_t n, size_t m) {
	if (n>Matrix<T>::rows && m>Matrix<T>::cols) {
        reallocate(n, m);
        for (int i=0; i<Matrix<T>::rows; i++) {
			std::fill(data[i]+Matrix<T>::cols, data[i]+m, 0);
		}
		for (int i=Matrix<T>::rows; i<n; i++) {
			std::fill(data[i], data[i]+m, 0);
		}

		BaseMatrix<T>::rows=n;
        BaseMatrix<T>::cols=m;
        return;
	}

	if (n>Matrix<T>::rows) {
		reallocate(n, m);
		for (int i=Matrix<T>::rows; i<n; i++) {
			std::fill(data[i], data[i]+Matrix<T>::cols, 0);
		}
	}

	if (m>Matrix<T>::cols) {
		reallocate(n, m);
		for (int i=0; i<n; i++) {
			std::fill(data[i]+Matrix<T>::cols, data[i]+m, 0);
		}
	}

	Matrix<T>::rows=n;
	Matrix<T>::cols=m;
}

template <typename T>
T& TableMatrix<T>::Get(size_t n, size_t m) const {
	if (n>= Matrix<T>::rows || m >= Matrix<T>::cols) {
		throw std::invalid_argument("Index out of range!");
	}
	return data[n][m];
}

template <typename T>
T* TableMatrix<T>::operator[](size_t ind) const {
	if (ind >= Matrix<T>::rows) {
		throw std::invalid_argument("Index out of range!");
	}
	return data[ind];
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator+(const T& a) const {
	if (Matrix<T>::Square()) {
		TableMatrix<T> matrix(*this);
		for (int i=0; i<Matrix<T>::rows; i++) {
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
		for (int i=0; i<Matrix<T>::rows; i++) {
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
	for (int i=0; i<Matrix<T>::rows; i++) {
		for (int j=0; j<Matrix<T>::columns; j++) {
			matrix.data[i][j]*=a;
		}
	}
	return matrix;
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator+(const TableMatrix<T>& m) const {
	if (Matrix<T>::rows == m.Matrix<T>::Rows() && Matrix<T>::cols == m.Matrix<T>::Cols()) {
		TableMatrix<T> matrix(m);
		for (int i=0; i<Matrix<T>::rows; i++) {
			for (int j=0; j<Matrix<T>::cols; j++) {
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
	if (Matrix<T>::rows == m.Matrix<T>::Rows() && Matrix<T>::cols == m.BaseMatrix<T>::Cols()) {
		TableMatrix<T> matrix(m);
		for (int i=0; i<Matrix<T>::rows; i++) {
			for (int j=0; j<Matrix<T>::cols; j++) {
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
    if (Matrix<T>::cols != rhs.Matrix<T>::Rows()){
        throw std::invalid_argument("Operation isn't permitted !");
    } else{
        TableMatrix<T> answer(Matrix<T>::rows, rhs.Matrix<T>::Cols());
        for (int i=0; i < answer.Matrix<T>::Rows(); ++i){
            for (int j=0; j < answer.Matrix<T>::Cols(); ++j){
                size_t index = 0;
                while (index < Matrix<T>::cols){
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
	if (Matrix<T>::rows!=m.Matrix<T>::Rows() || Matrix<T>::cols!=m.Matrix<T>::Cols()) {
		return false;
	}
	for (int i=0; i<Matrix<T>::rows; i++) {
		if (! std::equal(data[i], data[i]+Matrix<T>::cols, m.data[i], m.data[i]+Matrix<T>::cols)) {
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
	if (m.Matrix<T>::Rows()>Matrix<T>::rows || m.Matrix<T>::Cols()>Matrix<T>::cols) {
		reallocate(m.Matrix<T>::Rows(), m.Matrix<T>::Cols());
	}
	Matrix<T>::rows=m.Matrix<T>::Rows();
	Matrix<T>::cols=m.Matrix<T>::Cols();

	for (int i=0; i<Matrix<T>::cols; i++) {
		std::copy(m.data[i], m.data[i]+m.Matrix<T>::Cols(), data[i]);
	}
	return *this;

}

template <typename T>
void FlatMatrix<T>::reallocate(size_t n, size_t m) {
	T* new_data = new T [n*m];
	for (int i=0; i<Matrix<T>::rows; i++) {
		std::copy(data+i*Matrix<T>::cols, data+(i+1)*Matrix<T>::cols, new_data+i*m);
	}
	delete[]data;
	data = new_data;
}

template <typename T>
Matrix<T>::Matrix(size_t n, size_t m, T value): Matrix<T>(n, m) {
	data = new T[Matrix<T>::rows*Matrix<T>::cols];
	std::fill(data, data+Matrix<T>::rows*Matrix<T>::cols, value);
}

template <typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>>& a): Matrix<T>(a) {
	data = new T[Matrix<T>::rows*Matrix<T>::cols];
	int indi=0;
	for (auto i : A) {
        int indj = 0;
		for (auto j : i) {
			data[indi*Matrix<T>::cols+indj]=j;
            ++indj;
		}
		++indi;
	}
}

template <typename T>
FlatMatrix<T>::FlatMatrix(const FlatMatrix& m): Matrix<T>(m.Rows(), m.Cols()){
	data = new T[Matrix<T>::rows*Matrix<T>::cols];
	for (int i=0; i<Matrix<T>::rows; i++) {
		for (int j=0; j<Matrix<T>::cols; j++) {
			data[i*Matrix<T>::cols+j]=m.Get(i, j);
		}
	}
}

template <typename T>
FlatMatrix<T>::~FlatMatrix() {
	delete[]data;
}

template <typename T>
void FlatMatrix<T>::Resize(size_t n, size_t m) {
	if (n>Matrix<T>::rows && m>Matrix<T>::cols) {
        reallocate(n, m);
        for (int i=0; i<Matrix<T>::rows; i++) {
			std::fill(data+i*m+Matrix<T>::cols, data+(i+1)*m, 0);
		}
		std::fill(data+Matrix<T>::rows*m, data+m*n, 0);
		Matrix<T>::rows = n;
        Matrix<T>::cols = m;
	}
	else {
        if (n>Matrix<T>::rows) {
            reallocate(n, m);
            std::fill(data+Matrix<T>::rows*Matrix<T>::cols, data+m*n, 0);
        }
        if (m>Matrix<T>::cols) {
            reallocate(n, m);
            for (int i=0; i<n; i++) {
                std::fill(data+i*m+Matrix<T>::cols, data+(i+1)*m, 0);
            }
        }
        Matrix<T>::rows = n;
        Matrix<T>::cols = m;
	}

}

template <typename T>
T& FlatMatrix<T>::Get(size_t n, size_t m) const {
	if (n>= Matrix<T>::rows || m >= Matrix<T>::cols) {
		throw std::invalid_argument("Index out of range!");
	}
	return data[n*Matrix<T>::cols+m];
}

template <typename T>
T* FlatMatrix<T>::operator[](size_t index) const {
	if (index >= Matrix<T>::rows) {
		throw std::invalid_argument("Index out of range!");
	}
	return data+index*Matrix<T>::cols;
}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator+(const T& a) const {
	if (Matrix<T>::Square()) {
		FlatMatrix<T> matrix(*this);
		for (int i=0; i<Matrix<T>::rows; i++) {
			for (int j=0; j<Matrix<T>::cols; j++) {
				if (i==j) {
					matrix.data[i*Matrix<T>::cols+j]+=a;
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
	if (Matrix<T>::cols==m.Cols() && Matrix<T>::rows==m.Rows()) {
		FlatMatrix<T> matrix(m);
		for (int i=0; i<Matrix<T>::cols*Matrix<T>::rows; i++) {
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
	if (Matrix<T>::cols==m.Cols() && Matrix<T>::rows==m.Rows()) {
		FlatMatrix<T> matrix(*this);
		for (int i=0; i<Matrix<T>::Rows(); i++) {
			for (int j=0; j<Matrix<T>::Cols(); j++) {
				if (i==j) {
					matrix.data[i*Matrix<T>::Cols()+j]-=a;
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
	if (Matrix<T>::Columns()==m.Matrix<T>::Cols() && Matrix<T>::Rows()==m.Matrix<T>::Rows()) {
		FlatMatrix<T> matrix(m);
		for (int i=0; i<Matrix<T>::Cols()*Matrix<T>::Rows(); i++) {
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
	for (int i=0; i<Matrix<T>::rows*Matrix<T>::cols; i++) {
		matrix.data[i]*=a;
	}
	return matrix;
}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator*(const FlatMatrix<T>& m) const {
	if (Matrix<T>::cols==m.Matrix<T>::Rows()) {
		FlatMatrix<T> matrix(Matrix<T>::Rows(), m.Matrix<T>::Cols());
		for (int i=0; i<Matrix<T>::rows; i++) {
			for (int j=0; j<m.Matrix<T>::Cols(); j++) {
				T sum = 0;
				for (int index=0; index< Matrix<T>::cols; i++) {
					sum+=data[i*Matrix<T>::cols+index]*m.data[index*m.Matrix<T>::cols+j];
				}
				matrix.data[i*m.Matrix<T>::Cols()+j]=sum;
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
	if (Matrix<T>::rows!=m.Matrix<T>::Rows() || Matrix<T>::cols!=m.BaseMatrix<T>::Cols()) {
		return false;
	}
	return std::equal(data, data+Matrix<T>::cols*Matrix<T>::rows, m.data, m.data+m.Matrix<T>::Cols()*m.Matrix<T>::Rows());
}

template <typename T>
bool FlatMatrix<T>::operator!=(const FlatMatrix<T>& m) const {
	return !(*this==m);
}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator=(const FlatMatrix<T>& m) {
	Resize(m.Matrix<T>::rows, m.Matrix<T>::cols);
	for (int i=0; i<Matrix<T>::rows*Matrix<T>::cols; i++) {
        data[i] = m.data[i];
	}
	return *this;
}


