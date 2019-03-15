#ifndef SIMPLEX_CC
#define SIMPLEX_CC

#include "Simplex.h"

int Simplex::FindPivotColumn()
{
    auto pivot = min_element(c.begin(), c.end());
    if(*pivot >= 0)
    {
        is_optimal = true;
    }
    return pivot - c.begin();
}

int Simplex::FindPivotRow()
{
    int j = FindPivotColumn();
    std::vector<int> v(n_restrictions);

    for(int i = 0; i < n_restrictions; i++)
    {
        v[i] = ;
    }

}

#endif