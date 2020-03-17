#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "MatrixUtils.h"

int main()
{
    Matrix *A = (Matrix *)malloc(sizeof(Matrix));
    InitializeMatrix(A, 2, 2);
    t_double a[2][2] = {{4, 3}, {6, 3}};

    for(int i = 0; i < A->rows; i++)
    {
        for(int j = 0; j < A->rows; j++)
        {
            A->data[i][j] = a[i][j];
        }
    }

    LUDecomposition(A);

    DeleteMatrix(A);

    exit(0);
}