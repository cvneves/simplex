#include "RevisedSimplex.h"
#include "Simplex.h"

int RevisedSimplex::FindSmallestReducedCost()
{
    Eigen::VectorXd c_B(B.col(0).size()), reduced_costs(c.size());
    Eigen::MatrixXd p(1, B.col(0).size());

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

    long double biggest_c_j = reduced_costs[0];
    int biggest_index = 0;

    //find smallest reduced cost index
    for (int j = 1; j < reduced_costs.size(); j++)
    {
        // if (reduced_costs[j] - biggest_c_j > EPSILON)
        // {
        //     biggest_c_j = reduced_costs[j];
        //     biggest_index = j;
        // }

        if (reduced_costs[j] > EPSILON)
            return j;
    }

    //if (reduced_costs[biggest_index] <= EPSILON)
    return -1;

    //return biggest_index;
}

Eigen::VectorXd RevisedSimplex::ComputeU(int j)
{
    Eigen::VectorXd u(B.col(0).size());
    u = B.inverse() * A.col(j);

    return u;
}

int RevisedSimplex::FindSmallestTheta(Eigen::VectorXd u)
{

    long double greatest_u_j = u[0];
    int greatest_index = 0;

    for (int j = 1; j < u.size(); j++)
    {
        if (u[j] > greatest_u_j)
        {
            greatest_u_j = u[j];
            greatest_index = j;
        }
    }

    if (greatest_u_j < 0)
        return -1;

    Eigen::VectorXd x_B(B.col(0).size());
    x_B = B.inverse() * b;

    
    int i = 0;


    long double theta;

    for(int j = 0; j < x_B.size(); j++)
    {
        if(u[j] > 0 && x_B[j] >= 0)
        {
            theta = x_B[j] / u[j];
            break;
        }
    }

    for (int j = 0; j < x_B.size(); j++)
    {
        if (u[j] <= 0 || x_B[j] < 0)
            continue;

        long double theta_i = x_B[j] / u[j];

        if (theta_i < theta)
        {
            theta = theta_i;
            i = j;
        }
    }

    return basic_variables[i];
}

void RevisedSimplex::Solve()
{
    std::sort(basic_variables.begin(), basic_variables.end());
    std::sort(non_basic_variables.begin(), non_basic_variables.end());
    for (int j = 0; j < B.row(0).size(); j++)
    {
        B.col(j) = A.col(basic_variables[j]);
    }

    while (true)
    {
        std::cout << B << "\n\n";

        std::sort(basic_variables.begin(), basic_variables.end());
        std::sort(non_basic_variables.begin(), non_basic_variables.end());

        int entering_base = FindSmallestReducedCost();

        if (entering_base == -1)
            break;

        Eigen::VectorXd u = ComputeU(entering_base);

        int leaving_base = FindSmallestTheta(u);

        if (leaving_base == -1)
            break;

        std::cout << entering_base << ", " << leaving_base << "\n";

        int entering_index = std::find(non_basic_variables.begin(), non_basic_variables.end(), entering_base) - non_basic_variables.begin();
        int leaving_index = std::find(basic_variables.begin(), basic_variables.end(), leaving_base) - basic_variables.begin();

        std::swap(non_basic_variables[entering_index], basic_variables[leaving_index]);

        for (int j = 0; j < B.row(0).size(); j++)
        {
            B.col(j) = A.col(basic_variables[j]);
        }
    }

    Eigen::VectorXd c_B(B.col(0).size());
    for (int i = 0; i < c_B.size(); i++)
    {
        c_B[i] = c[basic_variables[i]];
    }

    std::cout << c_B.transpose() * (B.inverse() * b);
}