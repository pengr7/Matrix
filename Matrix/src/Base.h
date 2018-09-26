#ifndef BASE_H
#define BASE_H
template <typename T>
class Base {
    public:
		Base();  // Constructor
		virtual void set(T** X, int _row, int _column);  // Sets the values of all elements.
		virtual void set_one(T value, int pos_x, int pos_y);  // Sets the value of one specified element.
		virtual int* get_size();  // Returns the size.
		virtual T get(int pos_x, int pos_y);  // Returns the value of one specified element.
		virtual bool check_all(T* keys, int len);  // Checks if all of the entrys in a given raw array are in the data storage.
		virtual bool check_one(T* keys, int len);  // Checks if any of the entrys in a given raw array is in the data storage.
        T** x;  // Stores all elements. Use as data storage.
		int row;  // If it is a vector, row = 1.
		int column;  // Denotes the column of a matrix or dimension of a vector.
};
#endif

