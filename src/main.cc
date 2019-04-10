#include <iostream>
#include <fstream>

#include "RevisedSimplex.h"

#include "Simplex.h"
#include "Model.h"
#include "Parser.h"


int main(int argc, char *argv[])
{
    RevisedSimplex rv;

    rv.A = Eigen::MatrixXd(2,5);
    rv.B = Eigen::MatrixXd(2,2);

    rv.c = Eigen::VectorXd(5);
    rv.b = Eigen::VectorXd(2);
    rv.d = Eigen::VectorXd(5);
    rv.basic_variables = {3,4};
    rv.non_basic_variables = {0,1,2};


    rv.A << 3, 2, 1, 1, 0, 2, 5, 3, 0, 1;
    rv.B << 1, 0, 0, 1;

    rv.c << -2,-3,-4,0,0;
    rv.b << 10,15;


    rv.FindSmallestReducedCost();



}
