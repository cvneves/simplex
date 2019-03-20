#include <iostream>

#include "Simplex.h"

int main()
{
    Simplex a;
    //a.tableau = {{1, 2, 3, 4, 0, 0, 0}, {0, 3, 2, 1, 1, 0, 10}, {0, 2, 5, 3, 0, 1, 15}};
    a.tableau = {{1,-3,-2,0,0,0,0}, {0,-1,2,1,0,0,4}, {0,3,2,0,1,0,14}, {0,1,-1,0,0,1,3}};

   // std::cout << a.FindPivotColumn() << "\n";
   // std::cout << a.FindPivotRow(1) << "\n";

    a.Solve();
    
    std::cout << a.ToString();
}