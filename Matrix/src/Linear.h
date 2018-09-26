#ifndef LINEAR_H
#define LINEAR_H
#include "Base.cpp"
template <class T>
class Matrix:public Base<T> {
    public:
        Matrix();  // Constructor 1
        Matrix(Matrix &A);  // Constructor 2
        Matrix(int _row, int _column);  // Constructor 3
        void print();  // Prints the matrix.
        Matrix Row(int m);  // Gets one row of the matrix.
        Matrix Column(int n);  // Gets one column of the matrix.
        T max();  // Returns the maximum entry.
        T min();  // Returns the minimum entry.
        Matrix transpose();  // Returns the transpose of the current matrix.
        T det();  // Returns the determinant of the current matrix.
        Matrix<double> inverse();  // Returns the inverse of the current matrix if it is invertible.
        T operator()(int pos_x, int pos_y);  // Overloads the () operator.
        void setByFile(const char* file);  // Reads from ".txt" file to set elements for matrix.
        void printToFile(const char* file);  // Prints matrix to a ".txt" file.
        void sort(string s);  // To sort the elements of matrix in a ascending or descending sequence.
        void hear(string s, Matrix<T> &A);  // Receives two fixed format of arguments and work according to the them.
        template<typename T1>
        friend Matrix<T1> operator +(Matrix<T1> &A, Matrix<T1> &B);  // Overloading operator '+'.
        template<typename T1>
        friend Matrix<T1> operator -(Matrix<T1> &A, Matrix<T1> &B);  // Overloading operator '-'.
        template<typename T1>
        friend Matrix<T1> operator *(Matrix<T1> &A, Matrix<T1> &B);  // Overloading operator '*'.
};
template <class T>
istream& operator>>(istream &is, Matrix<T> &A);  // Stream overloading to input data into a matrix
template <class T>
ostream& operator<<(ostream &os, Matrix<T> &A);  // Stream overloading to output data of a matrix
template <class T>
class Vector:public Base<T> {
    public:
        Vector();  // Constructor 1
        Vector(Vector &a);  // Constructor 2
        explicit Vector(int _dim);  // Constructor 3
        int Dim();  // Returns the dimension of the vector.
        int length();  // Returns the length of the vector.
        void print();  // Prints the vector.
        T operator()(int pos);  // Overloads the () operator.
        void setByFile(const char* file);  // Reads from ".txt" file to set elements for vector.
		void printToFile(const char* file);  // Prints vector to a ".txt" file.
		void sort(string s);  // To sort the elements of vector in a ascending or descending sequence.
		void hear(string s, Vector<T> &a);  // Receives two fixed format of arguments and work according to the them.
        template<typename T1>
        friend Vector<T1> operator +(Vector<T1> &a, Vector<T1> &b);  // Overloading operator '+'.
        template<typename T1>
        friend Vector<T1> operator -(Vector<T1> &a, Vector<T1> &b);  // Overloading operator '-'.
        template<typename T1>
        friend Vector<T1> operator *(Vector<T1> &a, Vector<T1> &b);  // Overloading operator '*'.
};
template <class T>
istream& operator>>(istream &is, Vector<T> &a);  // Stream overloading to input data into a vector
template <class T>
ostream& operator<<(ostream &os, Vector<T> &a);  // Stream overloading to output data of a vector
#endif

