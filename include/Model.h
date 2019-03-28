#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <string>
#include <vector>

enum ConstraintType
{
    less_equal,
    equal,
    greater_equal
};

enum ObjectiveType
{
    maximize,
    minimize
};

class Constraint
{
  public:
    std::string name;
    std::map<std::string, double> column_value;
    std::map<std::string, double> rhs_value;

    ConstraintType constraint_type;
};

class Bound
{
  public:
    double value;
    enum BoundType
    {
        less_equal,
        greater_equal,
        equal
    };
    BoundType bound_type;
};

class Variable
{
  public:
    std::string name;
    std::map<std::string, std::vector<Bound>> bounds;
};

class Objective
{
  public:
    std::string name;
    std::map<std::string, double> cost_value;

    ObjectiveType objective_type;
};

class Model
{
  public:
    Objective objective_function;
    std::vector<Constraint> constraints;
    std::vector<Variable> variables;

    std::string ToString();
};

#endif