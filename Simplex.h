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
  std::vector<std::vector<double>> tableau;
  std::vector<int> B;

  int n_variables, n_restrictions;

  bool is_optimal, is_infeasible;

  double objective_value;

  void Solve();
  int FindPivotColumn();
  int FindPivotRow(int j);
  bool CheckOptimality();
  void Pivot(int r, int i, int j);
  bool CheckInfeasibility();

  std::string ToString();

};

#endif