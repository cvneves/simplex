#include "Constraint.h"
#include <iostream>

Constraint::Constraint(std::string n)
{
    name = n;
}

void Constraint::AddVariable(Variable var, double v)
{
    column_value[var.name] = v;
}

void Constraint::AddRhs(std::string r_n, double v)
{
    rhs_value[r_n] = v;
    main_rhs_value = v;
}

void Constraint::SetConstraintType(Constraint::ConstraintType c_t)
{
    constraint_type = c_t;
}

std::string Constraint::ToString()
{
    std::string to_string = "";
    for (auto v : column_value)
    {
        std::string sign = v.second < 0 ? "-" : "+";
        to_string += sign + " " + std::to_string(abs(v.second)) + "*" + v.first + " ";
    }

    std::string sign;

    switch (constraint_type)
    {
    case Constraint::less_equal:
        sign = "<=";
        break;
    case Constraint::equal:
        sign = "=";
        break;
    case Constraint::greater_equal:
        sign = ">=";
        break;
    }
    if (to_string.size() > 0)
        to_string.pop_back();

     to_string += " " + sign + " ";
     to_string += std::to_string(main_rhs_value);

    return to_string;
}