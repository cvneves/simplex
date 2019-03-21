#include <iostream>

#include "Simplex.h"

int main()
{
    /*https://jaredantrobus.com/squirrel/2015/Summer/MA162/4.1.php*/
    /*http://simplex.tode.cz/en/#steps*/

    Simplex a;
    //a.tableau = {{1, 2, 3, 4, 0, 0, 0}, {0, 3, 2, 1, 1, 0, 10}, {0, 2, 5, 3, 0, 1, 15}};
    a.tableau = {{1, -1, -2, -3,0,0,0}, {0,3,4,6,1,0,20}, {0,56,34,11,0,1,55}};
    a.basic_variables = {3,4};

    a.Solve();
    std::cout << a.objective_value << "\n";
    std::cout << a.ToString();
}