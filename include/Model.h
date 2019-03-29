#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <string>
#include <vector>

#include "Variable.h"
#include "Constraint.h"
#include "Objective.h"

class Model
{
  public:
    Objective objective_function;
    std::vector<Constraint> constraints;
    std::vector<Variable> variables;

    std::string ToString();

    void AddVariable(Variable);
    void AddConstraint(Constraint);
    void SetObjective(Objective);
    
};

#endif