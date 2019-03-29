#include "Variable.h"

Variable::Variable(std::string n)
{
    name = n;
}

Variable::Variable(std::string n, double l_b, double u_b)
{
    name = n;
    if (l_b != -std::numeric_limits<double>::infinity())
    {
        Bound lower_bound(l_b, Bound::greater_equal);
        bounds.push_back(lower_bound);
    }

    if (u_b != std::numeric_limits<double>::infinity())
    {
        Bound upper_bound(u_b, Bound::less_equal);
        bounds.push_back(upper_bound);
    }
}

Variable::Variable(std::string n, double fx_b)
{
    name = n;
    Bound fixed_bound(fx_b, Bound::equal);
    bounds.push_back(fixed_bound);
}

std::string Variable::ToString()
{
    std::string to_string = "";
    int n_bounds = bounds.size();

    if (n_bounds == 0)
        return name;

    for (auto bound : bounds)
    {
        switch (bound.bound_type)
        {
        case Bound::less_equal:
            to_string += name + " <= " + std::to_string(bound.value) + ", ";
            break;
        case Bound::greater_equal:
            to_string += name + " >= " + std::to_string(bound.value) + ", ";
            break;
        case Bound::equal:
            to_string += name + " = " + std::to_string(bound.value) + ", ";
            break;
        }
    }

    to_string.pop_back();
    to_string.pop_back();

    return to_string;
}