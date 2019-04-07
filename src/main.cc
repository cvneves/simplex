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
    std::string file_name = argv[1];
    m = ReadMps(file_name);
    //m.Print();

    m.StandardForm();

    //m.Print();

    m.Solve();

    

    //std::cout << m.simplex.ToString();

    std::cout << m.simplex.objective_value << "\n";
    

}