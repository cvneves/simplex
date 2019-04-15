#include "RevisedSimplex.h"
#include "Simplex.h"

int RevisedSimplex::FindSmallestReducedCost()
{
    Eigen::VectorXd c_B(B.col(0).size()), reduced_costs(non_basic_variables.size());
    Eigen::MatrixXd p(1, B.col(0).size());

    for (int i = 0; i < c_B.size(); i++)
    {
        c_B[i] = c[basic_variables[i]];
    }

    for (int j = 0; j < reduced_costs.size(); j++)
    {
        Eigen::VectorXd d_B(B.size());

        d_B = (-1) * B.inverse() * A.col(non_basic_variables[j]);

        reduced_costs[j] = c[non_basic_variables[j]] + (c_B.transpose() * d_B)[0];
    }

    std::cout << "c_j: " << reduced_costs.transpose() << "\n";

        for (int j = 0; j < reduced_costs.size(); j++)
    {
        if (reduced_costs[j] > 0)
            return non_basic_variables[j];
    }

    return -1;
}

Eigen::VectorXd RevisedSimplex::ComputeU(int j)
{
    Eigen::VectorXd u(B.col(0).size());
    u = B.inverse() * A.col(j);
    std::cout << "u: " << u.transpose() << "\n";
    return u;
}

int RevisedSimplex::FindSmallestTheta(Eigen::VectorXd u)
{

    long double greatest_u_j = u[0];
    for (int j = 1; j < u.size(); j++)
    {
        if (u[j] > greatest_u_j)
        {
            greatest_u_j = u[j];
        }
    }

    if (greatest_u_j < 0)
        return -1;

    Eigen::VectorXd x_B(B.col(0).size());
    x_B = B.inverse() * b;

    int i = 0;

    long double theta;

    for (int j = 0; j < x_B.size(); j++)
    {
        if (u[j] > 0)
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
    std::cout << "theta: " << theta << "\n";

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

        int entering_base = FindSmallestReducedCost();

        if (entering_base == -1)
            break;

        Eigen::VectorXd u = ComputeU(entering_base);

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

        std::cout << B << "\n";
        std::cout << "x_B: " << (B.inverse() * b).transpose() << "\n\n";
    }

    Eigen::VectorXd c_B(B.col(0).size());
    for (int i = 0; i < c_B.size(); i++)
    {
        c_B[i] = c[basic_variables[i]];
    }

    std::cout << c_B.transpose() * (B.inverse() * b);
}