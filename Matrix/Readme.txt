#Class10 14331226 PengRui Project05

This project can do some easy calculation about matrices and vectors.
Base.h is a header file which contains the base class including the common things between a matrix and a vector, and class Matrix and class Vector inherit from it. Templates were used to implement parametric polymorphism. All functions except the constructor are changed into virtual functions.
Base.cpp is a cpp file which contains the implement of the member functions of the classes declared in header file.
Linear.h is a header file which contains the declaration of the Matrix class and the Vector class.
Linear.cpp is a cpp file which contains the implement of the member functions of the classes declared in the header file. Functors are written for both Matrix and Vector class so that you can use the operator () to get a specified element. In addition to the original methods, now you can use the Matrix class to calculate the transpose, determinant and inverse of a current matrix. Also, stream operators are overloaded to easily input and output data, and some possible exceptions are considered. Functions to read and write file, sort and hear are implemented.
main.cpp can be used to display the functions of this project.
You can see the header files to see the detailed instruction of the variables and member functions of a class.
show.cpp is a new file in project06 for the simulation of movements of a robot arm with three joints using OpenGL. You can run a.out to display the functions.
