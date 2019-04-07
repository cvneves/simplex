#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>
#include <sstream>

#define EPSILON 1e-8

std::vector<long double>::iterator find_smallest(std::vector<long double>::iterator, std::vector<double>::iterator);

class Simplex
{
public:
  std::vector<std::vector<long double>> tableau;

  std::vector<int> basic_variables;
  std::vector<int> artificial_variables;
  std::vector<int> bad_variables;
  std::vector<long double> solution;

  bool is_optimal, is_infeasible;

  double objective_value;

  void Solve();
  int FindPivotColumn();
  int FindPivotRow(int j);
  bool CheckOptimality();
  void Pivot(int r, int i, int j);
  bool CheckInfeasibility();
  void CalculateSolution();

  std::string ToString();
};

#endif