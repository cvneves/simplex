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

    rv.A = Eigen::MatrixXd(2, 5);
    rv.B = Eigen::MatrixXd(2, 2);

    rv.c = Eigen::VectorXd(5);
    rv.b = Eigen::VectorXd(2);
    rv.d = Eigen::VectorXd(5);
    rv.basic_variables = {3, 4};
    rv.non_basic_variables = {0, 1, 2, 3};

    rv.A << 3, 2, 1, 1, 0, 2, 5, 3, 0, 1;

    for (int j = 0; j < rv.B.row(0).size(); j++)
    {
        rv.B.col(j) = rv.A.col(rv.basic_variables[j]);
    }

    rv.c << 2, 3, 4, 0, 0;
    rv.b << 10, 15;

    rv.Solve();
}
