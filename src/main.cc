#include <iostream>
#include <fstream>
#include "Simplex.h"
#include "Model.h"

int main(int argc, char* argv[])
{
    /*https://jaredantrobus.com/squirrel/2015/Summer/MA162/4.1.php*/
    /*http://simplex.tode.cz/en/#steps*/

    Model m;

    for(int i = 0; i < 10; i++)
    {
        Variable x("x" + std::to_string(i+1), 0 , std::numeric_limits<double>::infinity());
        m.AddVariable(x);
    }

    for(auto x : m.variables)
    {
        std::cout << x.ToString() << "\n";
    }
}