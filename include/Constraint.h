#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <string>
#include <vector>
#include <map>

class Constraint
{
  public:
    std::string name;
    std::map<std::string, double> column_value;
    std::map<std::string, double> rhs_value;
    double main_rhs_value;

    typedef enum
    {
        less_equal,
        equal,
        greater_equal
    } ConstraintType;

    ConstraintType constraint_type;

    Constraint(std::string);
    
    void AddVariable(std::string, double);
    void AddRhs(std::string, double);
    void SetConstraintType(ConstraintType);
    
    std::string ToString();

};

#endif