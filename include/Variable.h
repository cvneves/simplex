#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>
#include <map>

#include <limits>
#include "Bound.h"

class Variable
{
public:
  std::string name;
  std::vector<Bound> bounds;

  Variable(std::string);
  Variable(std::string, double, double);
  Variable(std::string, double);
  std::string ToString();
};

#endif