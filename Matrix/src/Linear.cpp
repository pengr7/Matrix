#include "Linear.h"
#include <math.h>
#include <iomanip>
#include <fstream>
int equalZero(const double x) {
    static const double Ep = 0.001;
    if (-Ep < x && x < Ep)
        return 1;
    return 0;
}
void swap(const int length, double *a, double *b) {
    double temp;
    int i;
    for (i = 0; i < length; ++i) {
        temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}
void add(const int length, double *a, const double *b, const double x) {
    int i;
    for (i = 0; i < length; ++i)
        a[i] += b[i]*x;
}
void multi(const int length, double *a, const double x) {
    int i;
    for (i = 0; i < length; ++i)
        a[i] *= x;
}  // These four functions above are used in calculating the inverse.
template <typename T>
T f(T** a, int n) {
	T s = 0, **p = new T* [n-1];
    for (i = 0; i < n-1; i++) p[i] = new T[n-1];
	if (n == 1) return a[0][0];
	for (k = 0; k < n; k++) {
		for (i = 0; i < n-1; i++)
			for (j = 0; j < n-1; j++)
				if (i < k) p[i][j] = a[i][j+1];
				else p[i][j] = a[i+1][j+1];
		s += (T)pow(-1, k)*a[k][0]*f((T**)p, n-1);
	}
	return s;
}  // This function is used in calculating the determinant.
template <class T>
Matrix<T>::Matrix() {
    Matrix::row = Matrix::column = 2;
    Matrix::x = new T *[Matrix::row];
    for (i = 0; i < Matrix::column; i++)
        Matrix::x[i] = new T[Matrix::column];
    for (i = 0; i < Matrix::row; i++)
        for (j = 0; j < Matrix::column; j++)
            Matrix::x[i][j] = 0;
}
template <class T>
Matrix<T>::Matrix(Matrix &A) {
    Matrix::row = A.row;
    Matrix::column = A.column;
    Matrix::x = new T *[Matrix::row];
    for (i = 0; i < Matrix::column; i++)
        Matrix::x[i] = new T[Matrix::column];
    for (i = 0; i < Matrix::row; i++)
        for (j = 0; j < Matrix::column; j++)
            Matrix::x[i][j] = A.x[i][j];
}
template <class T>
Matrix<T>::Matrix(int _row, int _column) {
    Matrix::row = _row;
    Matrix::column = _column;
    Matrix::x = new T* [Matrix::row];
    for (i = 0; i < Matrix::row; i++)
        Matrix::x[i] = new T[Matrix::column];
    for (i = 0; i < Matrix::row; i++)
        for (j = 0; j < Matrix::column; j++)
            Matrix::x[i][j] = 0;
}
template <class T>
void Matrix<T>::print() {
    for (i = 0; i < Matrix::row; i++) {
        cout << "|";
        for (j = 0; j < Matrix::column; j++)
            cout << setw(5) << Matrix::x[i][j];
        cout << " |" << endl;
    }
}
template <class T>
Matrix<T> Matrix<T>::Row(int m) {
	if (m < 1 || m > Matrix::row)
		throw invalid_argument("Out of range\n");
    Matrix A(1, Matrix::column);
    for (i = 0; i < Matrix::column; i++)
        A.x[0][i] = Matrix::x[m - 1][i];
    return A;
}
template <class T>
Matrix<T> Matrix<T>::Column(int n) {
	if (n < 1 || n > Matrix::column)
		throw invalid_argument("Out of range\n");
    Matrix A(Matrix::row, 1);
    for (i = 0; i < Matrix::row; i++)
        A.x[i][0] = Matrix::x[i][n - 1];
    return A;
}
template <class T>
T Matrix<T>::max() {
    T _max = Matrix::x[0][0];
    for (i = 0; i < Matrix::row; i++)
        for (j = 0; j < Matrix::column; j++)
            if (Matrix::x[i][j] > _max)
                _max = Matrix::x[i][j];
    return _max;
}
template <class T>
T Matrix<T>::min() {
    T _min = Matrix::x[0][0];
    for (i = 0; i < Matrix::row; i++)
        for (j = 0; j < Matrix::column; j++)
            if (Matrix::x[i][j] < _min)
                _min = Matrix::x[i][j];
    return _min;
}
template <class T>
Matrix<T> Matrix<T>::transpose() {
	Matrix<T> A(Matrix::column, Matrix::row);
	for (i = 0; i < A.row; i++)
		for (j = 0; j < A.column; j++)
			A.x[i][j] = Matrix::x[j][i];
	return A;
}
template <class T>
T Matrix<T>::det() {
	return f(Matrix::x, Matrix::row);
}
template <class T>
Matrix<double> Matrix<T>::inverse() {
	if (Matrix::row != Matrix::column)
		throw invalid_argument("Not invertible\n");
	int n = Matrix::row, m = n << 1, f = 1;
	Matrix<double> A(n, n);
    double matrix[30][60];
    for (i = 0; i < n; ++i) {
        matrix[i][n+i] = 1;
        for (j = 0; j < n; ++j)
            matrix[i][j] = Matrix::x[i][j];
    }
    for (i = 0; i < n && f; ++i) {
        if (equalZero(matrix[i][i])) {
            for (j = i+1; j < n && equalZero(matrix[j][i]); ++j)
                continue;
            if (j == n)
                f = 0;
            else
                swap(m, matrix[i], matrix[j]);
    	}
        if (f) {
            multi(m, matrix[i], 1/matrix[i][i]);
            for (j = i+1; j < n; ++j)
                if (equalZero(matrix[j][i]) == 0)
                    add(m, matrix[j], matrix[i], -matrix[j][i]);
        }
    }
    if (f) {
        for (i = n-1; i > 0; --i)
            for (j = i-1; j >= 0; --j)
                if (equalZero(matrix[j][i]) == 0)
                    add(m, matrix[j], matrix[i], -matrix[j][i]);
        for (i = 0; i < n; ++i) {
            for (j = n; j < m; ++j)
                A.set_one(matrix[i][j], i+1, j-n+1);
        }
    } else {
        cout << "Not Invertible!" << endl;
    }
    return A;
}
template <class T>
T Matrix<T>::operator()(int pos_x, int pos_y) {
	if (pos_x < 1 || pos_y < 1 || pos_x > Matrix::row || pos_y > Matrix::column)
		throw invalid_argument("Out of range\n");
	return Matrix::x[--pos_x][--pos_y];
}
template <class T>
void Matrix<T>::setByFile(const char* file) {
	ifstream in(file);
	for (i = 0; i < Matrix::row; i++)
		for (j = 0; j < Matrix::column; j++)
			in >> Matrix::x[i][j];
}
template <class T>
void Matrix<T>::printToFile(const char* file) {
	ofstream out(file);
	for (i = 0; i < Matrix::row; i++) {
		for (j = 0; j < Matrix::column-1; j++)
			out << Matrix::x[i][j] << " ";
		out << Matrix::x[i][Matrix::column-1] << endl;
	}
}
template <class T>
void Matrix<T>::sort(string s) {
	int size = Matrix::row*Matrix::column, cnt = 0;
	T tmp[size];
	for (i = 0; i < Matrix::row; i++)
		for (j = 0; j < Matrix::column; j++, cnt++)
			tmp[cnt] = Matrix::x[i][j];
	for (i = 0; i < size; i++)
		for (j = i+1; j < size; j++)
			if ((s == "ascending" && tmp[i] > tmp[j]) || (s == "descending" && tmp[i] < tmp[j])) {
				T temp = tmp[i];
				tmp[i] = tmp[j];
				tmp[j] = temp;
			}
	for (i = 0; i < Matrix::row; i++)
		for (j = 0; j < Matrix::column; j++)
			Matrix::x[i][j] = tmp[i*Matrix::column+j];
}
template <class T>
void Matrix<T>::hear(string s, Matrix<T> &A) {
	if (s == "I love")
		*this = *this + A;
	if (s == "I hate")
		*this = *this - A;
}
template <class T>
Matrix<T> operator +(Matrix<T> &A, Matrix<T> &B) {
	if (!(A.row == B.row && A.column == B.column))
		throw invalid_argument("Not matched\n");
    Matrix<T> C(A.row, A.column);
    for (i = 0; i < A.row; i++)
        for (j = 0; j < A.column; j++)
            C.x[i][j] = A.x[i][j] + B.x[i][j];
    return C;
}
template <class T>
Matrix<T> operator -(Matrix<T> &A, Matrix<T> &B) {
	if (!(A.row == B.row && A.column == B.column))
		throw invalid_argument("Not matched\n");
    Matrix<T> C(A.row, A.column);
    for (i = 0; i < A.row; i++)
        for (j = 0; j < A.column; j++)
            C.x[i][j] = A.x[i][j] - B.x[i][j];
    return C;
}
template <class T>
Matrix<T> operator *(Matrix<T> &A, Matrix<T> &B) {
	if (A.column != B.row)
		throw invalid_argument("Not matched\n");
    Matrix<T> C(A.row, B.column);
    for (i = 0; i < A.row; i++)
        for (j = 0; j < B.column; j++)
            for (k = 0; k < B.row; k++)
                C.x[i][j] += A.x[i][k] * B.x[k][j];
    return C;
}
template <class T>
Vector<T>::Vector() {
	Vector::row = 1;
    Vector::column = 2;
    Vector::x = new T*;
    Vector::x[0] = new T[Vector::column];
    for (i = 0; i < Vector::column; i++)
    	Vector::x[0][i] = 0;
}
template <class T>
Vector<T>::Vector(Vector &a) {
	Vector::row = a.row;
    Vector::column = a.column;
    Vector::x = new T*;
    Vector::x[0] = new T[Vector::column];
    for (i = 0; i < Vector::column; i++)
    	Vector::x[0][i] = a.x[0][i];
}
template <class T>
Vector<T>::Vector(int dim) {
	Vector::row = 1;
    Vector::column = dim;
    Vector::x = new T*;
    Vector::x[0] = new T[Vector::column];
    for (i = 0; i < Vector::column; i++)
    	Vector::x[0][i] = 0;
}
template <class T>
int Vector<T>::Dim() {
    return Vector::column;
}
template <class T>
int Vector<T>::length() {
    int sq = 0;
    for (i = 0; i < Vector::column; i++)
        sq += Vector::x[0][i] * Vector::x[0][i];
    return sqrt(sq);
}
template <class T>
void Vector<T>::print() {
    for (i = 0; i < Vector::column; i++)
        cout << "|" << setw(5) << Vector::x[0][i] << " |" << endl;
}
template <class T>
T Vector<T>::operator()(int pos) {
	if (pos > Vector::column || pos < 1)
		throw invalid_argument("Out of range\n");
	return Vector::x[0][--pos];
}
template <class T>
void Vector<T>::setByFile(const char* file) {
	ifstream in(file);
	for (i = 0; i < Vector::row; i++)
		for (j = 0; j < Vector::column; j++)
			in >> Vector::x[i][j];
}
template <class T>
void Vector<T>::printToFile(const char* file) {
	ofstream out(file);
	for (i = 0; i < Vector::row; i++) {
		for (j = 0; j < Vector::column-1; j++)
			out << Vector::x[i][j] << " ";
		out << Vector::x[i][Vector::column-1] << endl;
	}
}
template <class T>
void Vector<T>::sort(string s) {
	int size = Vector::row*Vector::column, cnt = 0;
	T tmp[size];
	for (i = 0; i < Vector::row; i++)
		for (j = 0; j < Vector::column; j++, cnt++)
			tmp[cnt] = Vector::x[i][j];
	for (i = 0; i < size; i++)
		for (j = i+1; j < size; j++)
			if ((s == "ascending" && tmp[i] > tmp[j]) || (s == "descending" && tmp[i] < tmp[j])) {
				T temp = tmp[i];
				tmp[i] = tmp[j];
				tmp[j] = temp;
			}
	for (i = 0; i < Vector::row; i++)
		for (j = 0; j < Vector::column; j++)
			Vector::x[i][j] = tmp[i*Vector::column+j];
}
template <class T>
void Vector<T>::hear(string s, Vector<T> &a) {
	if (s == "I love")
		*this = *this + a;
	if (s == "I hate")
		*this = *this - a;
}
template <class T>
Vector<T> operator +(Vector<T> &a, Vector<T> &b) {
	if (a.column != b.column)
		throw invalid_argument("Not matched\n");
    Vector<T> c(a.column);
    for (i = 0; i < a.column; i++)
        c.x[0][i] = a.x[0][i] + b.x[0][i];
    return c;
}
template <class T>
Vector<T> operator -(Vector<T> &a, Vector<T> &b) {
	if (a.column != b.column)
		throw invalid_argument("Not matched\n");
    Vector<T> c(a.column);
    for (i = 0; i < a.column; i++)
        c.x[0][i] = a.x[0][i] - b.x[0][i];
    return c;
}
template <class T>
Vector<T> operator *(Vector<T> &a, Vector<T> &b) {
	if (a.column != b.column)
		throw invalid_argument("Not matched\n");
    Vector<T> c(1);
    for (i = 0; i < a.column; i++)
        c.x[0][0] += a.x[0][i] * b.x[0][i];
    return c;
}
template <class T>
istream& operator>>(istream &is, Matrix<T> &A) {
	for (i = 0; i < A.row; i++)
		for (j = 0; j < A.column; j++)
			is >> A.x[i][j];
	return is;
}
template <class T>
ostream& operator<<(ostream &os, Matrix<T> &A) {
	A.print();
	return os;
}
template <class T>
istream& operator>>(istream &is, Vector<T> &a) {
	for (i = 0; i < a.row; i++)
		for (j = 0; j < a.column; j++)
			is >> a.x[i][j];
	return is;
}
template <class T>
ostream& operator<<(ostream &os, Vector<T> &a) {
	a.print();
	return os;
}

