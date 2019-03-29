#ifndef PROBLEM_CC
#define PROBLEM_CC

#include "Model.h"

std::string Model::ToString()
{
}

void Model::AddVariable(Variable x)
{
    variables.push_back(x);
}

void Model::AddConstraint(Constraint c)
{
    constraints.push_back(c);
}

void Model::SetObjective(Objective z)
{
    objective_function = z;
}

#endif