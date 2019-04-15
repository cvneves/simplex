#include <iostream>
#include <fstream>

#include "RevisedSimplex.h"

#include "Simplex.h"
#include "Model.h"
#include "Parser.h"

int main(int argc, char *argv[])
{
    /*    Model m;
    std::string file_name = argv[1];

    m = ReadMps(file_name);
    m.StandardForm();
    m.Solve();

    std::cout << m.simplex.objective_value; */

    RevisedSimplex rv;

    rv.A = Eigen::MatrixXd(3, 7);
    rv.B = Eigen::MatrixXd(3, 3);

    rv.c = Eigen::VectorXd(7);
    rv.b = Eigen::VectorXd(3);
    rv.d = Eigen::VectorXd(7);
    rv.basic_variables = {4,5,6};
    rv.non_basic_variables = {0,1,2,3};
    rv.A << 3, 2, 1, 2, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 4, 3, 3, 4, 0, 0, 1;

    rv.c << 19, 13, 12, 17, 0, 0, 0;
    rv.b << 225, 117, 420;

    rv.Solve();
}
