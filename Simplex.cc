#ifndef SIMPLEX_CC
#define SIMPLEX_CC

#include "Simplex.h"

std::string Simplex::ToString()
{
    std::string str = "";
    for(int i = 0; i < n_restrictions; i++)
    {
        for(int j = 0; j < n_variables; j++)
        {
            str += std::to_string(A[i][j]) + " ";

        }
        str += "\n";
    }

    return str;

}

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

void Simplex::Pivoting(std::vector<double>& row, int pivot_row, int pivot_column)
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

    for (int k : v)
    {
        row[k] = row[k] - row[pivot_column] * A[pivot_row][k] / A[pivot_row][pivot_column];
    }
    row[pivot_column] = 0;
}

void Simplex::ObjFunctionPivoting()
{
    
}

#endif