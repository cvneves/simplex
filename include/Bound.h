#ifndef BOUND_H
#define BOUND_H

#include <string>
#include <vector>
#include <map>

class Bound
{
  public:
    double value;

    typedef enum
    {
        less_equal,
        greater_equal,
        equal
    } BoundType;

    BoundType bound_type;

    Bound(double, BoundType);
};

#endif