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
    Variable x3("x3", 0, std::numeric_limits<double>::infinity());
    Variable x4("x4", 0, std::numeric_limits<double>::infinity());

    Constraint lim1("LIM1");
    lim1.AddVariable(x1, 1);
    lim1.AddVariable(x2, 1);
    lim1.AddVariable(x3, 1);
    lim1.AddVariable(x4, 1);
    lim1.AddRhs("R", 12);
    lim1.SetConstraintType(Constraint::less_equal);

    Objective z("COST", Objective::maximize);
    z.AddVariable(x1, 1);
    z.AddVariable(x2, 2);
    z.AddVariable(x3, 3);
    z.AddVariable(x4, 4);

    m.AddVariable(x1);
    m.AddVariable(x2);
    m.AddVariable(x3);
    m.AddVariable(x4);
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