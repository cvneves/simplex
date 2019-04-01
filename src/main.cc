#include <iostream>
#include <fstream>
#include "Simplex.h"
#include "Model.h"

int main(int argc, char *argv[])
{
    /*https://jaredantrobus.com/squirrel/2015/Summer/MA162/4.1.php*/
    /*http://simplex.tode.cz/en/#steps*/

    Model m;

    Variable x1("XONE", 0, INFINITY);
    Variable y2("YTWO", 0, INFINITY);
    Variable z3("ZTHREE", 0, INFINITY);

    Constraint lim1("LIM1");
    lim1.AddVariable(x1, 1);
    lim1.AddVariable(y2, 1);
    lim1.AddRhs("R", 5);
    lim1.SetConstraintType(Constraint::less_equal);

    Constraint lim2("LIM2");
    lim2.AddVariable(x1, 1);
    lim2.AddVariable(z3, 1);
    lim2.AddRhs("R", 10);
    lim2.SetConstraintType(Constraint::greater_equal);

    Constraint myeqn("MYEQN");
    myeqn.AddVariable(y2, -1);
    myeqn.AddVariable(z3, 1);
    myeqn.AddRhs("R", 7);
    myeqn.SetConstraintType(Constraint::equal);

    Objective z("COST", Objective::maximize);
    z.AddVariable(x1, 1);
    z.AddVariable(y2, 4);
    z.AddVariable(z3, 9);

    m.AddVariable(x1);
    m.AddVariable(y2);
    m.AddVariable(z3);
    m.AddConstraint(lim1);
    m.AddConstraint(lim2);
    m.AddConstraint(myeqn);
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