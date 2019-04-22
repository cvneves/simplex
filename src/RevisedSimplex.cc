#include "RevisedSimplex.h"
#include "Simplex.h"

int RevisedSimplex::FindSmallestReducedCost()
{
    Vec reduced_costs(non_basic_variables.size());
    Mat p(1, B.col(0).size());

    p = c_B.transpose() * B_inv;

    for (int j = 0; j < reduced_costs.size(); j++)
    {
        reduced_costs[j] = c[non_basic_variables[j]] - (p * A.col(non_basic_variables[j]))[0];
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

    theta = ratios[0];
    int j = 0;

    for (i = 1; i < ratios.size(); i++)
    {
        if (ratios[i] < theta - EPSILON)
        {
            theta = ratios[i];
            j = i;
        }
    }

    l = j;

    return basic_variables[j];
}

void RevisedSimplex::ComputeBInv(Vec u)
{

    for (int i = 0; i < B.rows(); i++)
    {
        if (i != l)
        {
            if (std::abs(u[i]) < EPSILON)
                continue;
            B_inv.row(i) += (-u[i] / u[l]) * B_inv.row(l);
        }
    }

    if (std::abs(u[l] - 1) > EPSILON)
        B_inv.row(l) /= u[l];
}

void RevisedSimplex::Solve()
{

    c_B = Vec(B.col(0).size());

    x_B = B_inv * b;

    x = Vec(A.cols());

    for (int i = 0; i < x_B.size(); i++)
    {
        x[basic_variables[i]] = x_B[i];
    }
    for (auto i : non_basic_variables)
    {
        x[i] = 0;
    }

    for (int i = 0; i < c_B.size(); i++)
    {
        c_B[i] = c[basic_variables[i]];
    }

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
        
        // x[entering_base] = theta;
        // x[leaving_base] = 0;
        // for (int i = 0; i < u.size(); i++)
        // {
        //     if (i == l)
        //         continue;
        //     x[basic_variables[i]] -= theta * u[i];
        // }

        // for (int i = 0; i < x_B.size(); i++)
        // {
        //     x_B[i] = x[basic_variables[i]];
        // }

        x_B[l] = theta;
        for (int i = 0; i < u.size(); i++)
        {
            if (i == l)
                continue;
            x_B[i] -= theta * u[i];
        }

        c_B[l] = c[entering_base];

        ComputeBInv(u);
        std::cout << c_B.transpose() * x_B << "\n";

        //B_inv = B.inverse();
        // std::cout << x_B.transpose() << "\n\n";
    }

    // std::cout << c_B.transpose() << "\n";

    std::cout << "\n";

    std::cout << c_B.transpose() * x_B << "\n";
}
