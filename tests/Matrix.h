#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>
#include <iostream>

#define EPSILON 1e-6

class Matrix
{

public:
  std::vector<std::vector<long double>> matrix;

  Matrix();
  Matrix(int, int);
  Matrix(std::vector<std::vector<long double>>);
  std::vector<long double> &operator[](int);

  std::string ToString();
  friend std::ostream &operator<<(std::ostream &os, Matrix A);

  int Rows();
  int Columns();
  Matrix Inverse();
  Matrix Transpose();
};

#endif