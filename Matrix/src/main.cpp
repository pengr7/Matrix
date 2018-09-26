#include "Linear.cpp"
int main() {
	try {
		Matrix<double> A, B(A), C(1, 2), D(2, 1);
    	double X[2][2] = {{3, 8}, {7, 4}};
    	double array[3] = {1, 3, 7};
    	A.set((double**)X, 2, 2);
    	A.set_one(4, 2, 2);
    	cout << "The given array is {1, 3, 7}" << endl;
    	cout << "Input the 2*2 matrix A: "; cin >> A;
    	cout << "Your input is in file mymatrix.txt." << endl; A.printToFile("mymatrix.txt");
    	B.setByFile("matrix.txt");
    	cout << "B = " << endl << B;
    	A.hear("I love", B); cout << "A hears love of B, A = " << endl << A;
    	A.hear("I hate", B); cout << "A hears hate of B, A = " << endl << A;
    	A.sort("ascending"); cout << "The ascending sequence of A = " << endl << A;
    	A.sort("descending"); cout << "The descending sequence of A = " << endl << A;
    	A.setByFile("matrix.txt");
    	cout << "The given A = " << endl << A;
    	cout << "The transpose of the A is: " << endl; B = A.transpose(); B.print();
    	cout << "The determinant of the A is: " << A.det() << endl;
    	cout << "The inverse of A is: " << endl; B = A.inverse(); B.print();
    	cout << "If all of the scalars in the array are in A: " << A.check_all(array, 3) << endl;
    	cout << "If any of the scalars in the array is in A: " << A.check_one(array, 3) << endl;
    	cout << "A's size is " << A.get_size()[0] << " * " << A.get_size()[1] << endl;
    	cout << "The (2, 2) entry of A is " << A(2, 2) << endl;
    	C = A.Row(1); cout << "The Row 1 of A is" << endl; C.print();
    	D = A.Column(2); cout << "The Column 2 of A is" << endl; D.print();
    	cout << "The maximum entry of A is " << A.max() << endl;
    	cout << "The minimun entry of A is " << A.min() << endl;
    	cout << "A + A = " << endl; B = A + A; B.print();
    	cout << "A - A = " << endl; B = A - A; B.print();
    	cout << "A * A = " << endl; B = A * A; B.print();

    	Vector<double> a, b(a), c(1);
    	double x[1][2] = {{3, 2}};
    	a.set((double**)x, 1, 2);
    	a.set_one(4, 1, 2);
    	cout << endl << "Input vector a with dimension 2: "; cin >> a;
    	cout << "Your input is in file myvector.txt." << endl; a.printToFile("myvector.txt");
    	b.setByFile("vector.txt");
    	cout << "b = " << endl << b;
    	a.hear("I love", b); cout << "a hears love of b, a = " << endl << a;
    	a.hear("I hate", b); cout << "a hears hate of b, a = " << endl << a;
    	a.sort("ascending"); cout << "The ascending sequence of a = " << endl << a;
    	a.sort("descending"); cout << "The descending sequence of a = " << endl << a;
    	a.setByFile("vector.txt");
    	cout << "The given a = " << endl << a;
    	cout << "If all of the scalars in the array are in a: " << a.check_all(array, 3) << endl;
    	cout << "If any of the scalars in the array are in a: " << a.check_one(array, 3) << endl;
    	cout << "The second entry of a is " << a(2) << endl;
    	cout << "The dimension of a is " << a.Dim() << endl;
    	cout << "The length of a is " << a.length() << endl;
    	cout << "a + a = " << endl; b = a + a; b.print();
    	cout << "a - a = " << endl; b = a - a; b.print();
    	cout << "a * a = " << endl; c = a * a; c.print();
	}
    catch(invalid_argument) {
    	cout << "ERROR" << endl;
	}
    return 0;
}

