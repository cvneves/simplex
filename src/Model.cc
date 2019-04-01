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
    std::vector<Variable> new_variables;
    std::vector<bool> used_variables;
    int i = 0;
    for (auto &v : variables)
    {

        if (v.lower_bound == 0)
        {
            used_variables.push_back(true);
            if (v.upper_bound == std::numeric_limits<double>::infinity())
                continue;
            else
            {
                Constraint c = Constraint(v.name + "_UP_BOUND");
                c.AddVariable(v, 1);
                c.SetConstraintType(Constraint::less_equal);
                c.AddRhs("NEW_RHS", v.upper_bound);
                AddConstraint(c);
            }
        }

        /* if (v.upper_bound == 0)
        {
            if (v.upper_bound == std::numeric_limits<double>::infinity())
                continue;
            else
            {
                Constraint c = Constraint(v.name + "_UP_BOUND");
                c.AddVariable(v, 1);
                c.SetConstraintType(Constraint::less_equal);
                c.AddRhs("NEW_RHS", v.upper_bound);
                AddConstraint(c);
            }
        } */

        else
        {
            used_variables.push_back(false);

            Variable v1 = Variable(v.name + "+", 0, std::numeric_limits<double>::infinity());
            Variable v2 = Variable(v.name + "-", 0, std::numeric_limits<double>::infinity());

            for (auto &c : constraints)
            {
                if (c.column_value.find(v.name) == c.column_value.end())
                    continue;
                c.column_value[v1.name] = c.column_value[v.name];
                c.column_value[v2.name] = -c.column_value[v.name];
                c.column_value.erase(v.name);
            }

            if (!(objective_function.cost_value.find(v.name) == objective_function.cost_value.end()))
            {
                objective_function.cost_value[v1.name] = objective_function.cost_value[v.name];
                objective_function.cost_value[v2.name] = -objective_function.cost_value[v.name];
                objective_function.cost_value.erase(v.name);
            }

            if (v.lower_bound != -std::numeric_limits<double>::infinity())
            {
                Constraint c = Constraint(v.name + "_LIM_LO");
                c.AddVariable(v1, 1);
                c.AddVariable(v2, -1);
                c.SetConstraintType(Constraint::greater_equal);
                c.AddRhs("NEW_RHS", v.lower_bound);
                AddConstraint(c);
            }
            if (v.upper_bound != std::numeric_limits<double>::infinity())
            {
                Constraint c = Constraint(v.name + "_LIM_UP");
                c.AddVariable(v1, 1);
                c.AddVariable(v2, -1);
                c.SetConstraintType(Constraint::less_equal);
                c.AddRhs("NEW_RHS", v.upper_bound);
                AddConstraint(c);
            }
            new_variables.push_back(v1);
            new_variables.push_back(v2);
        }
        i++;
    }

    std::vector<Variable> current_variables;
    for (int j = 0; j < variables.size(); j++)
    {
        if (used_variables[j] == true)
        {
            current_variables.push_back(variables[j]);
        }
    }

    variables = current_variables;

    for (auto v : new_variables)
    {
        AddVariable(v);
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
            c.AddVariable(slack, 1);
            c.constraint_type = Constraint::equal;
        }

        else if (c.constraint_type == Constraint::greater_equal)
        {
            std::string surplus_name = c.name + "_SURPLUS";
            Variable surplus(surplus_name, 0, std::numeric_limits<double>::infinity());
            AddVariable(surplus);
            c.AddVariable(surplus, -1);

            std::string artif_name = c.name + "_ART";
            Variable artificial(artif_name, 0, std::numeric_limits<double>::infinity());
            AddVariable(artificial);
            c.AddVariable(artificial, 1);

            c.constraint_type = Constraint::equal;

            objective_function.cost_value[artif_name] = M;
        }

        else
        {
            std::string artif_name = c.name + "_ART";
            Variable artificial(artif_name, 0, std::numeric_limits<double>::infinity());
            AddVariable(artificial);
            c.AddVariable(artificial, 1);

            objective_function.cost_value[artif_name] = M;
        }
    }
}

void Model::Solve()
{
    // convert to tableau
    std::vector<std::vector<double>> t = std::vector<std::vector<double>>(constraints.size() + 1, std::vector<double>(variables.size() + 1, 0));
    simplex.tableau = t;

    simplex.tableau[0][0] = 1;

    int i = 0;
    for (auto var : variables)
    {
        if (objective_function.cost_value.find(var.name) != objective_function.cost_value.end())
        {
            simplex.tableau[0][i + 1] = -objective_function.cost_value[var.name];
        }
        i++;
    }
    simplex.tableau[0].push_back(0);

    i = 1;
    for (auto constr : constraints)
    {
        int j = 0;
        for (auto var : variables)
        {
            if (constr.column_value.find(var.name) != constr.column_value.end())
            {
                simplex.tableau[i][j + 1] = constr.column_value[var.name];
            }
            j++;
        }
        i++;
    }

    i = 1;
    for (auto constr : constraints)
    {
        simplex.tableau[i].push_back(constr.main_rhs_value);
        i++;
    }

    //simplex.Solve();
}

#endif