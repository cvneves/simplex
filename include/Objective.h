#ifndef OBJECTIVE_H
#define OBJECTIVE_H

#include <string>
#include <vector>
#include <map>

class Objective
{
  public:
    std::string name;
    std::map<std::string, double> cost_value;

    typedef enum
    {
        maximize,
        minimize
    } ObjectiveType;

    ObjectiveType objective_type;

    Objective();
    Objective(std::string, ObjectiveType);

    void AddVariable(std::string, double);

    std::string ToString();
};

#endif