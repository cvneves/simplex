#include "RevisedSimplex.h"
#include "Simplex.h"

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
    //std::cout << reduced_costs;

    long double smallest_c_j = reduced_costs[0];
    int smallest_index = 0;


    //find smallest reduced cost index
    for(int j = 1; j < reduced_costs.size(); j++)
    {
        if(reduced_costs[j] - smallest_c_j < -2 * EPSILON)
        {
            smallest_c_j = reduced_costs[j];
            smallest_index = j;
        }
    }

    if(reduced_costs[smallest_index] >= 0 - EPSILON)
        return -1;
    

    return smallest_index;

}

Eigen::VectorXd RevisedSimplex::ComputeU(int j)
{
    Eigen::VectorXd u(B.col(0).size());
    u = B.inverse() * A.col(j);
    
    long double smallest_u_j = u[0];
    int smallest_index = 0;

    for(int j = 1; j < u.size(); j++)
    {
        if(u[j] - smallest_u_j < -2 * EPSILON)
        {
            smallest_u_j = u[j];
            smallest_index = j;
        }
    }

    if(u[smallest_index] <= 0 + EPSILON)
        // optimal cost is -infinity

    return u;
}
