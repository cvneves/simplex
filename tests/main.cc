#include <iostream>
#include "Matrix.h"

int main()
{
    Matrix A(3, 3);
    A.matrix = {{3, 8, 7}, {8, 7, 4}, {9, 8, 5}};

    std::cout << A << "\n";
    Matrix B = A.Inverse();

    std::cout << B;
}