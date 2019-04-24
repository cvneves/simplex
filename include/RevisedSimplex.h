#ifndef REVISEDSIMPLEX_H
#define REVISEDSIMPLEX_H

#include "Eigen/Dense"
#include <vector>
#include <iostream>
#include <algorithm>

typedef Eigen::Matrix< long double, Eigen::Dynamic, 1              > Vec;
typedef Eigen::Matrix< long double, Eigen::Dynamic, Eigen::Dynamic > Mat;

class RevisedSimplex
{
public:
  Mat A, B, B_inv, B_u, p;
  Vec x, d, c, b, x_B, c_B, u;
  long double theta;
  int l;

  std::vector<bool> basic_variables, non_basic_variables;

  int FindSmallestReducedCost();
  Vec ComputeU(int);
  int FindSmallestTheta(Vec);
  void ComputeBInv(Vec);
  void Solve();
  
};

#endif
