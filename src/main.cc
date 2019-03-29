#include <iostream>
#include <fstream>
#include "Simplex.h"
#include "Model.h"

int main(int argc, char *argv[])
{
    /*https://jaredantrobus.com/squirrel/2015/Summer/MA162/4.1.php*/
    /*http://simplex.tode.cz/en/#steps*/

    Model m;

    Variable x1("XONE", -std::numeric_limits<double>::infinity(), 4);
    Variable y2("YTWO", -1, 1);
    Variable z3("ZTHREE");

    m.AddVariable(x1);
    m.AddVariable(y2);
    m.AddVariable(z3);

    Constraint lim1("LIM1");
    lim1.AddVariable("XONE", 1);
    lim1.AddVariable("YTWO", 4);
    lim1.AddVariable("ZTHREE", 9);
    lim1.AddRhs("R", 5);
    lim1.SetConstraintType(Constraint::less_equal);

    Constraint lim2("LIM2");
    lim2.AddVariable("XONE", 1);
    lim2.AddVariable("ZTHREE", 1);
    lim1.AddRhs("R", 10);
    lim1.SetConstraintType(Constraint::greater_equal);

    Constraint myeqn("MYEQN");
    myeqn.AddVariable("YTWO", -1);
    myeqn.AddVariable("ZTHREE", 1);
    myeqn.AddRhs("R", 7);
    myeqn.SetConstraintType(Constraint::equal);

}