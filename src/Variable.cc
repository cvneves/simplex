#include "Variable.h"

Variable::Variable(std::string n)
{
    name = n;
    lower_bound = -std::numeric_limits<double>::infinity();
    upper_bound = std::numeric_limits<double>::infinity();
}

Variable::Variable(std::string n, double l_b, double u_b)
{
    name = n;
    lower_bound = l_b;
    upper_bound = u_b;
}

Variable::Variable(std::string n, double fx_b)
{
    name = n;
    upper_bound = lower_bound = fx_b;
}

std::string Variable::ToString()
{
    std::string to_string = "";

    if (lower_bound == upper_bound)
        to_string = name + " = " + std::to_string(upper_bound);

    else if (lower_bound == -std::numeric_limits<double>::infinity() && upper_bound == std::numeric_limits<double>::infinity())
        to_string = name;

    else if (lower_bound == -std::numeric_limits<double>::infinity())
        to_string = name + " <= " + std::to_string(upper_bound);

    else if (upper_bound == std::numeric_limits<double>::infinity())
        to_string = name + " >= " + std::to_string(lower_bound);

    else
        to_string = std::to_string(lower_bound) + " <= " + name + " <= " + std::to_string(upper_bound);

    return to_string;
}