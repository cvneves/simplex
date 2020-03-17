#ifndef MATRIXUTILS_H
#define MATRIXUTILS_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define EPSILON 0.0001
typedef float t_double;

typedef struct Matrix
{
    t_double **data;
    size_t rows, cols;
} Matrix;

void InitializeMatrix(Matrix *A, int rows, int cols);
void DeleteMatrix(Matrix *A);
void PrintMatrix(Matrix *A);
int MultiplyMatrix(Matrix *A, Matrix *B, Matrix *C);

void LUDecomposition(Matrix *A);

#endif