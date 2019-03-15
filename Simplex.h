#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

class Simplex
{
  public:
    int n_variables, n_restrictions;
    std::vector<double> c, b;
    std::vector<double> current_solution;
    bool is_optimal;
    std::vector<std::vector<double>> A, B, N;

    int FindPivotColumn();
    int FindPivotRow();
    void Pivoting(std::vector<double>& row, int i, int pivot_row, int pivot_column);
};

#endif