#ifndef PROBLEM_CC
#define PROBLEM_CC

#include "Model.h"
#include <iostream>
#include <limits>

std::string Model::ToString()
{
    std::string to_string = "";
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

void Model::StandardForm()
{
    if (objective_function.objective_type == Objective::minimize)
    {
        objective_function.objective_type = Objective::maximize;
        for (auto &v : objective_function.cost_value)
        {
            v.second = -v.second;
        }
    }

    for (auto &c : constraints)
    {
        if (c.constraint_type == Constraint::less_equal)
        {
            std::string slack_name = c.name + "_SLACK";
            Variable slack(slack_name, 0, std::numeric_limits<double>::infinity());
            AddVariable(slack);
            c.AddVariable(slack_name, 1);
            c.constraint_type = Constraint::equal;
        }

        if (c.constraint_type == Constraint::greater_equal)
        {
            std::string surplus_name = c.name + "_SURPLUS";
            Variable surplus(surplus_name, 0, std::numeric_limits<double>::infinity());
            AddVariable(surplus);
            c.AddVariable(surplus_name, -1);

            std::string artif_name = c.name + "_ART";
            Variable artificial(artif_name, 0, std::numeric_limits<double>::infinity());
            AddVariable(artificial);
            c.AddVariable(artif_name, 1);

            c.constraint_type = Constraint::equal;

            objective_function.cost_value[artif_name] = M;
        }

        if (c.constraint_type == Constraint::equal)
        {
            std::string artif_name = c.name + "_ART";
            Variable artificial(artif_name, 0, std::numeric_limits<double>::infinity());
            AddVariable(artificial);
            c.AddVariable(artif_name, 1);

            objective_function.cost_value[artif_name] = M;
        }
    }
}

#endif