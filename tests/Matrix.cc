#include "Matrix.h"

Matrix::Matrix()
{
}
Matrix::Matrix(int rows, int columns)
{
    matrix = std::vector<std::vector<long double>>(rows, std::vector<long double>(columns, 0));
}

Matrix::Matrix(std::vector<std::vector<long double>> A)
{
    matrix = A;
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
    Matrix A;
    {
        Matrix identity_matrix = Matrix(Rows(), Columns());

        std::vector<std::vector<long double>> vec = this->matrix;

        for (int i = 0; i < identity_matrix.Rows(); i++)
        {
            for (int j = 0; j < identity_matrix.Rows(); j++)
            {
                if (i == j)
                    identity_matrix[i][j] = 1;
            }
        }

        int i = 0;
        for (auto &v : vec)
        {
            v.insert(v.end(), identity_matrix[i].begin(), identity_matrix[i].end());
            i++;
        }

        A = Matrix(vec);
    }

    for (int i = 1; i < A.Rows(); i++)
    {

        for (int k = 0; k < i; k++)
        {
            int pivot_row;

            for (int ii = 0; ii < A.Rows(); ii++)
            {
                if (ii == i)
                    continue;
                if (A[ii][k] > EPSILON || A[ii][k] < -EPSILON)
                    pivot_row = ii;
            }

            long double element = A[i][k] / A[pivot_row][k];

            for (int j = 0; j < A.Columns(); j++)
            {
                A[i][j] -= A[pivot_row][j] * element;
            }
        }
    }

    for(int i = A.Rows() - 2; i >=0; i--)
    {
        
    }

    return A;
}

Matrix Matrix::Transpose()
{
    Matrix A = *this;

    if (this->Rows() == this->Columns())
    {
        for (int k = 0; k < Rows(); k++)
        {
            for (int i = k; i < Rows(); i++)
            {
                std::swap(A[i][k], A[k][i]);
            }
        }
    }

    return A;
}

std::ostream &operator<<(std::ostream &os, Matrix A)
{
    os << A.ToString();
    return os;
}