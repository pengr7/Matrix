#include "Base.h"
#include <iostream>
#include <stdexcept>
using namespace std;
int i, j, k, cnt;
template <class T>
Base<T>::Base():x(NULL), row(0), column(0) {}
template <class T>
void Base<T>::set(T** X, int _row, int _column) {
    row = _row;
    column = _column;
    x = new T* [row];
    for (i = 0; i < row; i++)
        x[i] = new T[column];
    for (i = 0; i < row; i++)
        for (j = 0; j < column; j++)
            x[i][j] = *((T*)X + i*column + j);
}
template <class T>
void Base<T>::set_one(T value, int pos_x, int pos_y) {
	if (pos_x < 1 || pos_y < 1 || pos_x > row || pos_y > column)
		throw invalid_argument("Out of range\n");
	x[--pos_x][--pos_y] = value;
}
template <class T>
int* Base<T>::get_size() {
    int* size = new int[2];
    size[0] = row;
    size[1] = column;
    return size;
}
template <class T>
T Base<T>::get(int pos_x, int pos_y) {
	if (pos_x < 1 || pos_y < 1 || pos_x > row || pos_y > column)
		throw invalid_argument("Out of range\n");
    return x[--pos_x][--pos_y];
}
template <class T>
bool Base<T>::check_all(T* keys, int len) {
	for (i = 0; i < len; i++) {
		cnt = 0;
		for (j = 0; j < row; j++)
        	for (k = 0; k < column; k++)
        		if (x[j][k] == keys[i])
        			cnt = 1;
        if (cnt == 0) break;
	}
	if (i == len)
		return true;
	return false;
}
template <class T>
bool Base<T>::check_one(T* keys, int len) {
	for (i = 0; i < len; i++)
		for (j = 0; j < row; j++)
        	for (k = 0; k < column; k++)
        		if (x[j][k] == keys[i])
        			return true;
	return false;
}

