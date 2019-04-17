#include "RevisedSimplex.h"
#include "Simplex.h"

int RevisedSimplex::FindSmallestReducedCost()
{
    Vec c_B(B.col(0).size()), reduced_costs(non_basic_variables.size());
    Mat p(1, B.col(0).size());

    for (int i = 0; i < c_B.size(); i++)
    {
        c_B[i] = c[basic_variables[i]];
    }

    for (int j = 0; j < reduced_costs.size(); j++)
    {
        Vec d_B(B.size());

        d_B = (-1) * B_inv * A.col(non_basic_variables[j]);

        reduced_costs[j] = c[non_basic_variables[j]] + (c_B.transpose() * d_B)[0];
    }

    for (int j = 0; j < reduced_costs.size(); j++)
    {
        if (reduced_costs[j] > EPSILON)
            return non_basic_variables[j];
    }

    return -1;
}

Vec RevisedSimplex::ComputeU(int j)
{
    Vec u(B.col(0).size());
    u = B_inv * A.col(j);
    return u;
}

int RevisedSimplex::FindSmallestTheta(Vec u)
{

    long double greatest_u_j = u[0];
    for (int j = 1; j < u.size(); j++)
    {
        if (u[j] > greatest_u_j + EPSILON)
        {
            greatest_u_j = u[j];
        }
    }

    if (greatest_u_j < EPSILON)
        return -1;

    Vec x_B(B.col(0).size());
    x_B = B_inv * b;

    int i = 0;

    Vec ratios(u.size());

    for (i = 0; i < ratios.size(); i++)
    {
        if (u[i] > EPSILON)
            ratios[i] = x_B[i] / u[i];
        else
        {
            ratios[i] = std::numeric_limits<long double>::infinity();
        }
    }

    long double theta = ratios[0];
    int j = 0;

    for (i = 1; i < ratios.size(); i++)
    {
        if (ratios[i] < theta - EPSILON)
        {
            theta = ratios[i];
            j = i;
        }
    }

    return basic_variables[j];
}

void RevisedSimplex::ComputeBInv(Vec u)
{
    for(int j = 0; j < B.cols(); j++)
    {
        B_u.col(j) = B.col(j);
    }
    for(int i = 0; i < B.rows(); i++)
    {
        B_u(i, B_u.size()-1) = u[i];
    }

    

}

void RevisedSimplex::Solve()
{
    std::sort(basic_variables.begin(), basic_variables.end());
    std::sort(non_basic_variables.begin(), non_basic_variables.end());

    for (int j = 0; j < B.row(0).size(); j++)
    {
        B.col(j) = A.col(basic_variables[j]);
    }

    B_inv = B.inverse();
    B_u = Mat(B.cols(), B.cols() + 1);

    while (true)
    {

        int entering_base = FindSmallestReducedCost();

        if (entering_base == -1)
            break;

        Vec u = ComputeU(entering_base);

        int leaving_base = FindSmallestTheta(u);

        if (leaving_base == -1)
            break;

        int entering_index = std::find(non_basic_variables.begin(), non_basic_variables.end(), entering_base) - non_basic_variables.begin();
        int leaving_index = std::find(basic_variables.begin(), basic_variables.end(), leaving_base) - basic_variables.begin();

        std::swap(non_basic_variables[entering_index], basic_variables[leaving_index]);

        std::sort(basic_variables.begin(), basic_variables.end());
        std::sort(non_basic_variables.begin(), non_basic_variables.end());

        for (int j = 0; j < B.row(0).size(); j++)
        {
            B.col(j) = A.col(basic_variables[j]);
        }

        // Eigen::VectorXd c_B(B.col(0).size());
        // for (int i = 0; i < c_B.size(); i++)
        // {
        //     c_B[i] = c[basic_variables[i]];
        // }

        // std::cout << c_B.transpose() * B.inverse() * b << "\n";

        Vec c_B(B.col(0).size());
        for (int i = 0; i < c_B.size(); i++)
        {
            c_B[i] = c[basic_variables[i]];
        }

        // show
        B_inv = B.inverse();

        std::cout << c_B.transpose() * B_inv * b << "\n";
    }

    Vec c_B(B.col(0).size());
    for (int i = 0; i < c_B.size(); i++)
    {
        c_B[i] = c[basic_variables[i]];
    }

    std::cout << c_B.transpose() * B_inv * b << "\n";
}
