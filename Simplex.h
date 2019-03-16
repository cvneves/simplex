#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>
#include <sstream>

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
    void Pivoting(std::vector<double>& row, int pivot_row, int pivot_column);
    void ObjFunctionPivoting();

    void Solve();
    
    std::string ToString();

};

#endif