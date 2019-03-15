#include <iostream>

#include "Simplex.h"

int main()
{
    Simplex a;
    a.c = {24,55,33,7,10};
    std::cout << a.FindPivotColumn();
}