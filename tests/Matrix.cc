#include "Matrix.h"

Matrix::Matrix(int rows, int columns)
{
    matrix = std::vector<std::vector<long double>>(rows, std::vector<long double>(columns, 0));
}

std::vector<long double> &Matrix::operator[](int j)
{
    return matrix[j];
}

std::string Matrix::ToString()
{
    std::string to_string = "";

    for (auto &row : matrix)
    {
        for (auto &value : row)
        {
            to_string += std::to_string(value) + " ";
        }
        to_string += "\n";
    }

    return to_string;
}

int Matrix::Rows()
{
    return matrix.size();
}

int Matrix::Columns()
{
    return matrix[0].size();
}

Matrix Matrix::Inverse()
{
    Matrix A = *this;
    Matrix inverted_matrix = Matrix(Rows(), Columns());
    // Matrix identity = Matrix(Rows(), Columns());

    for (int i = 0; i < inverted_matrix.Rows(); i++)
    {
        for (int j = 0; j < inverted_matrix.Rows(); j++)
        {
            if (i == j)
                inverted_matrix[i][j] = 1;
        }
    }

    for (int i = 1; i < Rows(); i++)
    {
        int pivot_row;

        for (int ii = 0; ii < Rows(); ii++)
        {
            if (ii == i)
                continue;
            if (A[ii][0] > EPSILON || A[ii][0] < EPSILON)
                pivot_row = ii;
        }

        long double element = A[i][0] / A[pivot_row][0];

        for(int j = 0; j < Columns(); j++)
        {
            A[i][j] -= A[pivot_row][j] * element;
        }
    }

    return A;
}

std::ostream &operator<<(std::ostream &os, Matrix A)
{
    os << A.ToString();
    return os;
}