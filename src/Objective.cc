#include "Objective.h"

Objective::Objective() {}

Objective::Objective(std::string n, ObjectiveType o_t)
{
    name = n;
    objective_type = o_t;
}

