#include "Objective.h"

Objective::Objective() {}

Objective::Objective(std::string n, ObjectiveType o_t)
{
    name = n;
    objective_type = o_t;
}

void Objective::AddVariable(std::string n, double v)
{
    cost_value[n] = v;
}

std::string Objective::ToString()
{
    std::string to_string;

    to_string = objective_type == maximize ? "Max: " : "Min: ";

    for (auto v : cost_value)
    {
        std::string sign = v.second < 0 ? "-" : "+";
        to_string += sign + " " + std::to_string(abs(v.second)) + "*" + v.first + " ";
    }

//    std::string sign;

//    to_string.pop_back();

//    to_string += " " + sign + " ";
//    to_string += std::to_string(main_rhs_value);

    return to_string;
}