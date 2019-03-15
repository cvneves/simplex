#include <iostream>

#include "Simplex.h"

int main()
{
    Simplex a;
    a.n_restrictions = 2;
    a.n_variables = 5;
    a.c = {-2, -3, -4};
    a.A = {{3, 2, 1, 1, 0}, {2, 5, 3, 0, 1}};
    a.b = {10, 15};

    int i = a.FindPivotRow();
    int j = a.FindPivotColumn();

    a.Pivoting(a.A[1], 0, i, j);

    for (int X = 0; X < 5; X++)
    {
        std::cout << a.A[0][X] << " ";
    }
    std::cout << std::endl;
}