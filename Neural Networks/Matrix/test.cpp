#include "Matrix.cpp"

#include<iostream>

int main()
{

    Matrix A = Matrix(3,3);
    Matrix B = Matrix(3,3);

    Matrix C = A.multiply(B);
    
    return 0;
 
}

