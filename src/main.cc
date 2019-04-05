#include <iostream>
#include <fstream>
#include "Simplex.h"
#include "Model.h"
#include "Parser.h"

int main(int argc, char *argv[])
{
    /*https://jaredantrobus.com/squirrel/2015/Summer/MA162/4.1.php*/
    /*http://simplex.tode.cz/en/#steps*/

    Model m;

    /*Variable x1("x1", -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
    Variable x2("x2", -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());

    Constraint lim1("LIM1");
    lim1.AddVariable(x1, 2);
    lim1.AddVariable(x2, 2);

    lim1.AddRhs("R", 12);
    lim1.SetConstraintType(Constraint::equal);

    Objective z("COST", Objective::maximize);
    z.AddVariable(x1, 1);
    z.AddVariable(x2, 1);

    m.AddVariable(x1);
    m.AddVariable(x2);

    m.AddConstraint(lim1);

    m.SetObjective(z);*/
 
    std::string file_name = argv[1];
    m = ReadMps(file_name);
    m.StandardForm(); 

    std::cout << m.objective_function.ToString() << "\n";

    for (auto c : m.constraints)
    {
        std::cout << c.ToString() << "\n";
    }
    for (auto v : m.variables)
    {
        std::cout << v.ToString() << "\n";
    } 


    m.Solve();

    //std::cout << m.simplex.tableau[0][1] << "\n"
    
    for (int i = 0; i < m.simplex.tableau.size(); i++)
    {
   //     std::cout << m.simplex.tableau[i][1] << "\n";
    }
    //std::cout << m.simplex.ToString();
    std::cout << "\n" << m.simplex.objective_value << "\n";
}