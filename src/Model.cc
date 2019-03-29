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

    for (auto &v : variables)
    {
        if (v.bounds.size() == 0)
        {
            Variable v_plus(v.name + "+", 0, std::numeric_limits<double>::infinity());
            Variable v_minus(v.name + "-", 0, std::numeric_limits<double>::infinity());

            std::vector<double> v1;

            for (auto &c : constraints)
            {
                //c.column_value[];
                //c.AddVariable(v_plus, v.value);
                //c.AddVariable(v_minus, -v.value);
            }
        }
    }

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
        if (c.main_rhs_value < 0)
        {
            c.main_rhs_value *= -1;
            for (auto &v : c.column_value)
            {
                v.second *= -1;
            }
            switch (c.constraint_type)
            {
            case Constraint::equal:
                break;
            case Constraint::less_equal:
                c.constraint_type = Constraint::greater_equal;
                break;
            case Constraint::greater_equal:
                c.constraint_type = Constraint::less_equal;
                break;
            }
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

        else if (c.constraint_type == Constraint::greater_equal)
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

        else
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