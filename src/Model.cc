#ifndef PROBLEM_CC
#define PROBLEM_CC

#include "Model.h"
#include <iostream>
#include <limits>

void Model::Print()
{
    std::cout << objective_function.ToString() << "\n";

    std::cout << "Subject to: \n";
    for (auto c : constraints)
    {
        std::cout << c.ToString() << "\n";
    }
    for (auto v : variables)
    {
        std::cout << v.ToString() << "\n";
    }
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
            slack.initial_basic = 1;
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
            artificial.initial_basic = 1;
            artificial.is_artificial = 1;
            AddVariable(artificial);
            c.AddVariable(artificial, 1);

            c.constraint_type = Constraint::equal;

            objective_function.cost_value[artif_name] = -M;
        }

        else
        {
            std::string artif_name = c.name + "_ART";
            Variable artificial(artif_name, 0, std::numeric_limits<double>::infinity());
            artificial.initial_basic = 1;
            artificial.is_artificial = 1;
            AddVariable(artificial);
            c.AddVariable(artificial, 1);

            objective_function.cost_value[artif_name] = -M;
        }
    }
}

void Model::Solve()
{
    // convert to tableau
    std::vector<std::vector<long double>> t = std::vector<std::vector<long double>>(constraints.size() + 1, std::vector<long double>(variables.size() + 1, 0));
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

    i = 0;
    for (auto v : variables)
    {
        if (v.is_artificial == true)
            simplex.artificial_variables.push_back(i);
        if (v.initial_basic == true)
            simplex.basic_variables.push_back(i);
        else
            simplex.non_basic_variables.push_back(i);

        i++;
    }

    // GETTING RID OF ARTIFICIAL VARIABLES
    std::vector<int> artificial_rows;

    for (auto art_var : simplex.artificial_variables)
    {

        for (int ii = 1; ii < simplex.tableau.size(); ii++)
        {
            if (simplex.tableau[ii][art_var + 1] != 0)
            {
                artificial_rows.push_back(ii);
            }
        }
    }

    if (simplex.artificial_variables.size() > 0)
    {
        for (auto art_row : artificial_rows)
        {
            for (int jj = 0; jj < simplex.tableau[0].size(); jj++)
            {
                simplex.tableau[0][jj] -= M * simplex.tableau[art_row][jj];
            }
        }
    }

    // simplex.Solve();

    // REVISED SIMPLEX

    // PHASE I

    revised_simplex.c = Vec(simplex.tableau[0].size() - 2);
    revised_simplex.A = Mat(simplex.tableau.size() - 1, simplex.tableau[0].size() - 2);
    revised_simplex.b = Vec(simplex.tableau.size() - 1);
    revised_simplex.B = Mat(revised_simplex.A.col(0).size(), revised_simplex.A.col(0).size());
    revised_simplex.basic_variables = std::vector<int>();
    revised_simplex.non_basic_variables = std::vector<int>();

    i = 0;
    for (auto var : variables)
    {
        //   if (objective_function.cost_value.find(var.name) != objective_function.cost_value.end())
        //    revised_simplex.c[i] = objective_function.cost_value[var.name];
        if (var.is_artificial == true)
        {
            revised_simplex.c[i] = -1;
        }
        else
        {
            revised_simplex.c[i] = 0;
        }
        i++;
    }

    i = 0;
    for (auto constr : constraints)
    {
        int j = 0;
        for (auto var : variables)
        {
            if (constr.column_value.find(var.name) != constr.column_value.end())
            {
                revised_simplex.A(i, j) = constr.column_value[var.name];
            }
            else
            {
                revised_simplex.A(i, j) = 0;
            }

            j++;
        }
        i++;
    }

    i = 0;
    for (auto constr : constraints)
    {
        revised_simplex.b[i] = constr.main_rhs_value;
        i++;
    }

    i = 0;
    for (auto v : variables)
    {
        if (v.is_artificial == true || v.initial_basic == true)
            revised_simplex.basic_variables.push_back(i);
        else
            revised_simplex.non_basic_variables.push_back(i);
        i++;
    }

    std::sort(revised_simplex.basic_variables.begin(), revised_simplex.basic_variables.end());
    std::sort(revised_simplex.non_basic_variables.begin(), revised_simplex.non_basic_variables.end());

    for (int j = 0; j < revised_simplex.B.row(0).size(); j++)
    {
        revised_simplex.B.col(j) = revised_simplex.A.col(revised_simplex.basic_variables[j]);
    }

    revised_simplex.B_inv = revised_simplex.B.inverse();

    revised_simplex.Solve();

    // PHASE 2

    int non_artificial_variables = 0;

    for (auto var : variables)
    {
        //   if (objective_function.cost_value.find(var.name) != objective_function.cost_value.end())
        //    revised_simplex.c[i] = objective_function.cost_value[var.name];
        if (var.is_artificial == false)
            non_artificial_variables++;
    }

    {
        Mat new_A(revised_simplex.A.rows(), non_artificial_variables);

        i = 0;
        for (int j = 0; j < revised_simplex.A.cols(); j++)
        {
            if ((variables.begin() + j)->is_artificial == false)
            {
                new_A.col(i) = revised_simplex.A.col(j);
                i++;
            }
        }

        revised_simplex.A = new_A;

        revised_simplex.c = Vec(new_A.cols());

        i = 0;
        for (auto var : variables)
        {
            //   if (objective_function.cost_value.find(var.name) != objective_function.cost_value.end())
            //    revised_simplex.c[i] = objective_function.cost_value[var.name];
            if (var.is_artificial == true)
            {
                continue;
            }
            else
            {
                revised_simplex.c[i] = objective_function.cost_value[var.name];
                i++;
            }
        }
    }

    for (auto v : revised_simplex.basic_variables)
    {
        (variables.begin() + v)->initial_basic = true;
    }
    for (auto v : revised_simplex.non_basic_variables)
    {
        (variables.begin() + v)->initial_basic = false;
    }

    revised_simplex.basic_variables.clear();
    revised_simplex.non_basic_variables.clear();

    i = 0;
    for (auto v : variables)
    {
        if (v.is_artificial == true)
            continue;
        else
        {
            if (v.initial_basic == true)
            {
                revised_simplex.basic_variables.push_back(i);
                i++;
            }
            else
            {
                revised_simplex.non_basic_variables.push_back(i);
                i++;
            }
        }
    }

    i = 0;
    for (auto v : revised_simplex.basic_variables)
    {
        revised_simplex.B.col(i) = revised_simplex.A.col(v);
        i++;
    }

    revised_simplex.B_inv = revised_simplex.B.inverse();

    //   std::cout << revised_simplex.A << "\n\n";
    //   std::cout << revised_simplex.B << "\n\n";
    //  std::cout << revised_simplex.c << "\n\n";

    revised_simplex.Solve();
}

#endif
