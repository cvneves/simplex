#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <vector>
#include <algorithm>

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
};

#endif