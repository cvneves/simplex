#include "RevisedSimplex.h"
#include "Simplex.h"

int RevisedSimplex::FindSmallestReducedCost()
{
    /*  Vec reduced_costs(non_basic_variables.size());
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

    return -1; */
}

Vec RevisedSimplex::ComputeU(int j)
{
    /* Vec u(B.col(0).size());
    u = B_inv * A.col(j);
    return u; */
}

int RevisedSimplex::FindSmallestTheta(Vec u)
{

    /*  long double greatest_u_j = u[0];
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

    return basic_variables[j]; */
}

void RevisedSimplex::ComputeBInv(Vec u)
{

    /*    for (int i = 0; i < B.rows(); i++)
    {
        if (i != l)
        {
            if (std::abs(u[i]) < EPSILON)
                continue;
            B_inv.row(i) += (-u[i] / u[l]) * B_inv.row(l);
        }
    }

    if (std::abs(u[l] - 1) > EPSILON)
        B_inv.row(l) /= u[l]; */
}

void RevisedSimplex::Solve()
{
    p = Mat(1, B.cols());
    c_B = Vec(B.cols());
    u = Vec(B.cols());

    Vec reduced_costs(A.cols() - B.cols());

    //B_inv = B.inverse();
    x_B = B_inv * b;

    std::vector<int> basic(B.cols()), non_basic(A.cols() - B.cols());

    x = Vec(A.cols());

    Mat B_inv_test = B_inv, B_inv_2 = B_inv;

    for (int i = 0, j = 0, k = 0; i < basic_variables.size(); i++)
    {
        if (basic_variables[i] == true)
        {
            x[i] = x_B[j];
            basic[j] = i;
            j++;
            continue;
        }
        non_basic[k] = i;
        k++;
        x[i] = 0;
    }

    std::vector<bool> last_basic_variables;

    int invert_step_size = 0;
    int invert = 0;

    while (true)
    {

        last_basic_variables = basic_variables;

        for (int j = 0, i = 0; j < basic_variables.size(); j++)
        {
            if (basic_variables[j] == false)
                continue;
            c_B[i] = c[j];
            i++;
        }

        p = c_B.transpose() * B_inv;

        for (int j = 0, i = 0; j < c.size(); j++)
        {
            if (basic_variables[j] == true)
                continue;
            reduced_costs[i] = c[j] - (p * A.col(j))[0];
            i++;
        }

        int entering_base;
        for (int i = 0, j = 0; j < basic_variables.size(); j++)
        {
            if (basic_variables[j] == false)
            {
                if (reduced_costs[i] > EPSILON)
                {
                    entering_base = j;
                    break;
                }
                i++;
            }
            if (i == reduced_costs.size() - 1)
                entering_base = -1;
        }

        if (entering_base == -1)
            break;

        u = B_inv * A.col(entering_base);

        int leaving_base;
        long double greatest_u_j = u[0];
        for (int j = 1; j < u.size(); j++)
        {
            if (u[j] > greatest_u_j + EPSILON)
            {
                greatest_u_j = u[j];
            }
        }

        if (greatest_u_j < EPSILON)
            leaving_base = -1;

        if (leaving_base == -1)
        {
            break;
        }

        Vec ratios(u.size());

        for (int i = 0; i < x_B.size(); i++)
        {
            //     if(x_B[i] < EPSILON)
            //        x_B[i] = 0;
        }

        for (int i = 0; i < ratios.size(); i++)
        {
            if (u[i] > EPSILON)
            {
                ratios[i] = x_B[i] / u[i];
            }
            else
            {
                ratios[i] = std::numeric_limits<long double>::infinity();
            }
        }

        theta = std::numeric_limits<long double>::infinity();
        leaving_base = 0;

        for (int i = 0, j = 0; i < basic_variables.size(); i++)
        {
            if (basic_variables[i] == false)
                continue;
            if (ratios[j] < theta - EPSILON)
            {
                theta = ratios[j];
                leaving_base = i;
                l = j;
            }
            j++;
        }

        basic_variables[entering_base] = true;
        basic_variables[leaving_base] = false;
        std::swap(*(std::find(basic.begin(), basic.end(), leaving_base)), *(std::find(non_basic.begin(), non_basic.end(), entering_base)));

        for (int i = 0; i < basic_variables.size(); i++)
        {
        }

        for (int i = 0, j = 0; i < basic_variables.size(); i++)
        {
            if (basic_variables[i] == false)
                continue;
            B.col(j) = A.col(i);
            j++;
        }

        for (int i = 0; i < B_inv_test.rows(); i++)
        {
            if (i != l)
            {
                if (std::abs(u[i]) < EPSILON)
                    continue;
                B_inv_test.row(i) += (-u[i] / u[l]) * B_inv_test.row(l);
            }
        }
        if (std::abs(u[l] - 1) > EPSILON)
            B_inv_test.row(l) /= u[l];

        x[entering_base] = theta;

        for (int i = 0, j = 0; i < last_basic_variables.size(); i++)
        {
            if (last_basic_variables[i] == true)
            {
                if (i != leaving_base)
                {
                    x[i] = x_B[j] - theta * u[j];
                }
                j++;
            }
        }

        for (int i = 0, j = 0; i < basic_variables.size(); i++)
        {
            if (basic_variables[i] == true)
            {
                x_B[j] = x[i];
                j++;
            }
        }

        // for (int i = 0, k = 0; i < basic_variables.size(); i++)
        // {
        //     if (basic_variables[i] == true)
        //         k++;

        //     if (i == leaving_base)
        //     {
        //         k--;
        //         for (int j = leaving_base; j > entering_base; j--)
        //         {
        //             if (basic_variables[j] == true)
        //             {
        //                 B_inv_test.row(k).swap(B_inv_test.row(k - 1));
        //                 k--;
        //             }
        //         }
        //         break;
        //     }
        // }

        // if (invert < invert_step_size)
        // {
        //     B_inv = B_inv_test;
        //     invert++;
        // }
        // else
        // {
        //     B_inv = B.inverse();
        //     invert = 0;
        // }

        for (int i = 0, j = 0; i < basic_variables.size(); i++)
        {
            if (basic_variables[i] == true)
            {
                int k = std::find(basic.begin(), basic.end(), i) - basic.begin();
                B_inv.row(j) = B_inv_test.row(k);
                std::cout << k << ", " << j << "\n\n";
                j++;
            }
        }

        std::cout << "\n\n---------------------------------------\n\n";

        for (int i = 0; i < basic.size(); i++)
            std::cout << basic[i] << " ";
        std::cout << "\n";
        for (int i = 0; i < non_basic.size(); i++)
            std::cout << non_basic[i] << " ";
        std::cout << "\n";

        std::sort(basic.begin(), basic.end());
        std::sort(non_basic.begin(), non_basic.end());

        //B_inv = B_inv_test;

        //B_inv_2 = B_inv;

        //B_inv = B.inverse();

        // x_B = B_inv * b;

        //std::cout << entering_base << ", " << leaving_base << "\n";
        //std::cout << c_B.transpose() * x_B << "\n";

        // // std::cout << "B_inv: \n"
        // //           << B_inv << "\n\n";
        // // std::cout << "B_inv_1: \n"
        // //           << B_inv_test << "\n\n";
        // //std::cout << "x_B: " << x_B.transpose() << "\n";
        // // std::cout << "c_B: " << c_B.transpose() << "\n\n";
        // // std::cout << "u: " << u.transpose() << "\n\n";
        // // std::cout << "j = " << entering_base << ", l = " << leaving_base << "\n\n";

        // // for (int i = 0; i < last_basic_variables.size(); i++)
        // // {
        // //     std::cout << last_basic_variables[i] << " ";
        // // }
        // // std::cout << "\n";
        // // for (int i = 0; i < basic_variables.size(); i++)
        // // {
        // //     std::cout << basic_variables[i] << " ";
        // // }
        // // std::cout << "\n";

        //std::cout << B.inverse() << "\n\n";
        //std::cout << B_inv_test << "\n\n";
        std::cout << B_inv << "\n\n";
        std::cout << B_inv_test << "\n\n";
        // std::cout << c_B.transpose() * x_B << "\n";

        std::cout << "\n\n---------------------------------------\n\n";
    }

    std::cout << c_B.transpose() * x_B << "\n";
}
