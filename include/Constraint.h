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
    
    typedef enum
    {
        less_equal,
        equal,
        greater_equal
    } ConstraintType;
    
    ConstraintType constraint_type;
};

#endif