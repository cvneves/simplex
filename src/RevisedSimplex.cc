#include "RevisedSimplex.h"
#include <iostream>

int RevisedSimplex::FindSmallestReducedCost()
{
    Eigen::VectorXd c_B(B.size()), reduced_costs(c.size());

    for (int i = 0; i < c_B.size(); i++)
    {
        c_B[i] = c[basic_variables[i]];
    }

    for (int j = 0; j < c.size(); j++)
    {
        for (auto &i : non_basic_variables)
        {
            if(j == i)
                d[i] = 1;
            else 
                d[i] = 0;            
        }

        Eigen::VectorXd d_B(B.size());

        d_B = (-1) * B.inverse() * A.col(j);

        for(int i = 0; i < basic_variables.size(); i++)
        {
            d[basic_variables[i]] = d_B[i];
        }

       std::cout << c_B.transpose() << "\n";
    }


}