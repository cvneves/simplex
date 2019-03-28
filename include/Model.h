#ifndef PROBLEM_H
#define PROBLEM_H

#include <map>
#include <string>

class Constraint
{

  public:
    std::map<std::string, double> column_value;
    std::map<std::string, double> rhs_value;

    enum ConstraintType
    {
        less_equal,
        equal,
        greater_equal
    };

};

class Bound : public Constraint
{
  public:
};

class Variable
{
  public:
    std::string name;
    std::map<std::string, Bound> bound_values;
};

class Objective
{
  public:
    std::map<std::string, double> cost_value;
    enum ObjectiveType
    {
        maximize,
        minimize
    };
};

class Model
{
  public:
};

#endif