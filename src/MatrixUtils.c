#include "MatrixUtils.h"

void InitializeMatrix(Matrix *A, int rows, int cols)
{
    A->data = malloc(rows * sizeof(t_double *));
    A->rows = rows;
    A->cols = cols;
    for (int i = 0; i < rows; i++)
    {
        A->data[i] = malloc(cols * sizeof(t_double));
    }
}
void DeleteMatrix(Matrix *A)
{
    for (int i = 0; i < A->rows; i++)
    {
        free(A->data[i]);
    }
    free(A->data);
    free(A);
}
void PrintMatrix(Matrix *A)
{
    for (int i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < A->cols; j++)
        {
            printf("%g ", A->data[i][j]);
        }
        printf("\n");
    }
}

int MultiplyMatrix(Matrix *A, Matrix *B, Matrix *C)
{
    if (A->cols != B->rows)
        return -1;
    InitializeMatrix(C, A->rows, B->cols);

    for (int i = 0; i < C->rows; i++)
    {
        for (int j = 0; j < C->cols; j++)
        {
            t_double sum = 0;
            for (int k = 0; k < A->rows; k++)
            {
                sum += A->data[i][k] * B->data[k][j];
            }
            C->data[i][j] = sum;
        }
    }

    return 0;
}

void LUDecomposition(Matrix *A)
{
    int N = A->cols;

    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            A->data[j][i] /= A->data[i][i];

            for (int k = i + 1; k < N; k++)
            {
                A->data[j][k] -= A->data[j][i] * A->data[i][k];
            }
        }
    }

    Matrix *U = malloc(sizeof(Matrix));
    InitializeMatrix(U, N, N);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (j >= i)
            {
                U->data[i][j] = A->data[i][j];
            }
            else
            {
                U->data[i][j] = 0;
            }
        }
    }

    Matrix *L = malloc(sizeof(Matrix));
    InitializeMatrix(L, N, N);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (j < i)
            {
                L->data[i][j] = A->data[i][j];
            }
            else if (j == i)
                L->data[i][j] = 1;
            else
            {
                L->data[i][j] = 0;
            }
        }
    }

    Matrix *C = malloc(sizeof(Matrix));
    MultiplyMatrix(L, U, C);

    PrintMatrix(C);
}