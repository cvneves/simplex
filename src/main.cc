#include <iostream>
#include <fstream>
#include "Simplex.h"
#include "Model.h"

int main(int argc, char *argv[])
{
    /*https://jaredantrobus.com/squirrel/2015/Summer/MA162/4.1.php*/
    /*http://simplex.tode.cz/en/#steps*/

    Model m;

    

    Variable x1("x1", 0, std::numeric_limits<double>::infinity());
    Variable x2("x2", 0, std::numeric_limits<double>::infinity());

    Constraint lim1("LIM1");
    lim1.AddVariable(x1, 4);
    lim1.AddVariable(x2, 3);
    lim1.AddRhs("R", 12);
    lim1.SetConstraintType(Constraint::equal);

    Objective z("COST", Objective::minimize);
    z.AddVariable(x1, 2);
    z.AddVariable(x2, 1);

    m.AddVariable(x1);
    m.AddVariable(x2);
    m.AddConstraint(lim1);

    m.SetObjective(z);

    std::cout << m.objective_function.ToString() << "\n";

    for (auto c : m.constraints)
    {
        std::cout << c.ToString() << "\n";
    }
    for (auto v : m.variables)
    {
        std::cout << v.ToString() << "\n";
    }

    m.StandardForm();

    std::cout << "\n";

    std::cout << m.objective_function.ToString() << "\n";

    for (auto c : m.constraints)
    {
        std::cout << c.ToString() << "\n";
    }
    for (auto v : m.variables)
    {
        std::cout << v.ToString() << "\n";
    }
    std::cout << "\n";

    
    m.Solve();
    std::cout << m.simplex.ToString();
}