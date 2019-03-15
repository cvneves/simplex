#ifndef SIMPLEX_CC
#define SIMPLEX_CC

#include "Simplex.h"

int Simplex::FindPivotColumn()
{
    auto pivot = min_element(c.begin(), c.end());
    if (*pivot >= 0)
    {
        is_optimal = true;
    }
    return pivot - c.begin();
}

int Simplex::FindPivotRow()
{
    int j = FindPivotColumn();
    std::vector<double> v(n_restrictions);

    for (int i = 0; i < n_restrictions; i++)
    {
        if (A[i][j] == 0)
            v[i] = std::numeric_limits<double>::max();
        else
            v[i] = b[i] / A[i][j];
    }
    auto i = min_element(v.begin(), v.end());

    return i - v.begin();
}

void Simplex::Pivoting(std::vector<double> &row, int i, int pivot_row, int pivot_column)
{
    std::vector<int> v;
    for (int j = 0; j < n_variables; j++)
    {
        if (j == pivot_column)
        {
            continue;
        }
        v.push_back(j);
    }

    row[pivot_column] = 0;

    for (int k : v)
    {
        row[k] = A[i][k] - A[i][pivot_column] * A[pivot_row][k] / A[pivot_row][pivot_column];
    }
}

#endif