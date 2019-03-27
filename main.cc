#include <iostream>

#include "Simplex.h"

int main()
{
    /*https://jaredantrobus.com/squirrel/2015/Summer/MA162/4.1.php*/
    /*http://simplex.tode.cz/en/#steps*/

    Simplex a;
    double M = 10000;
    //a.tableau = {{1, 2, 3, 4, 0, 0, 0}, {0, 3, 2, 1, 1, 0, 10}, {0, 2, 5, 3, 0, 1, 15}};
    a.tableau = {{1, 1000000, 0, 1000000, -1.0, 0, -9.0, -4.0, 0}, {0, 0, 0, 1, 0, 0, 1.0, -1.0, 7.0}, {0, 1, 0, 0, 1.0, -1.0, 1.0, 0, 10.0}, {0, 0, 1.0, 0, 1.0, 0, 0, 1.0, 5.0}};
    a.basic_variables = {0,1,2};
std::cout << a.ToString();
    a.Solve();
    std::cout << a.objective_value << "\n";
    std::cout << a.ToString(); 

    

}