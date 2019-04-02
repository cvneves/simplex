#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>
#include <map>

#include <limits>


class Variable
{
public:
  std::string name;
  double lower_bound, upper_bound;

  Variable(std::string);
  Variable(std::string, double, double);
  Variable(std::string, double);
  std::string ToString();
  bool initial_basic;
};

#endif