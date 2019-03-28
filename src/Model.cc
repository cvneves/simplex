#ifndef PROBLEM_CC
#define PROBLEM_CC

#include "Model.h"

std::string Model::ToString()
{
    std::string obj_func;
    obj_func = objective_function.objective_type == maximize ? "Max " : "Min ";

    for(auto it = objective_function.cost_value.begin(); it != objective_function.cost_value.end(); ++it)
    {
        obj_func += std::to_string(*it);
    }
}

#endif