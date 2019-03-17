#include <iostream>

#include "Simplex.h"

int main()
{
    Simplex a;
    //a.tableau = {{1, 2, 3, 4, 0, 0, 0}, {0, 3, 2, 1, 1, 0, 10}, {0, 2, 5, 3, 0, 1, 15}};
    a.tableau = {{1,2,3,0,0,0},{0,5,4,0,0,32},{0,1,2,0,0,10}};


    std::cout << a.ToString() << "\n";

    a.Solve();
    
    std::cout << a.ToString();
}