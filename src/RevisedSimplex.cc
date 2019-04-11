#include "RevisedSimplex.h"

int RevisedSimplex::FindSmallestReducedCost()
{
    Eigen::VectorXd c_B(B.col(0).size()), reduced_costs(c.size());
    Eigen::MatrixXd p(1, B.col(0).size());

    std::sort(basic_variables.begin(), basic_variables.end());
    std::sort(non_basic_variables.begin(), non_basic_variables.end());


    for (int i = 0; i < c_B.size(); i++)
    {
        c_B[i] = c[basic_variables[i]];
    }
    
    p = c_B.transpose() * B.inverse();


    for (int j = 0; j < c.size(); j++)
    {
        for (auto &i : non_basic_variables)
        {
            if (j == i)
                d[i] = 1;
            else
                d[i] = 0;
        }

        Eigen::VectorXd d_B(B.size());

        d_B = (-1) * B.inverse() * A.col(j);

        for (int i = 0; i < basic_variables.size(); i++)
        {
            d[basic_variables[i]] = d_B[i];
        }
  
        //reduced_costs[j] = c[j] - (p * A.col(j))[0];
        reduced_costs[j] = c[j] + (c_B.transpose() * d_B)[0];


    }
    std::cout << reduced_costs;
}