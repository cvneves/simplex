#ifndef SIMPLEX_CC
#define SIMPLEX_CC

#include "Simplex.h"

std::vector<long double>::iterator find_smallest(std::vector<long double>::iterator a, std::vector<long double>::iterator b)
{
    long double smallest = *a;
    std::vector<long double>::iterator it = a;
    ++a;
    for (a; a != b; ++a)
    {
        if (*a - smallest < -2 * EPSILON)
        {
            smallest = *a;
            it = a;
        }
    }
    return it;
}

int Simplex::FindPivotColumn()
{
       int j;
    j = find_smallest(tableau[0].begin() + 1, tableau[0].end() - 1) - tableau[0].begin();

    // int j;
    // for (j = 1; j < tableau[0].size() - 1; j++)
    // {
    //     if (tableau[0][j] < 0)
    //     {
    //         return j;
    //     }
    // }
    return j;
}

int Simplex::FindPivotRow(int j)
{
    std::vector<long double> v(tableau.size(), std::numeric_limits<long double>::infinity());
    int negative_count = 0;
    for (int i = 1; i < tableau.size(); i++)
    {
        if (tableau[i][j] <= 0 + EPSILON)
            continue;
        v[i - 1] = (tableau[i][tableau[0].size() - 1] / tableau[i][j]);
    }

    int i = find_smallest(v.begin(), v.end()) - v.begin() + 1;

    return i;
}

void Simplex::Pivot(int r, int i, int j)
{
    std::vector<long double> v = tableau[r];
    for (int n = 0; n < tableau[r].size(); n++)
    {
        if (n == j)
            v[n] = 0;
        v[n] = tableau[r][n] - tableau[r][j] * tableau[i][n] / tableau[i][j];
    }
    tableau[r] = v;
}

bool Simplex::CheckOptimality()
{

    if (*find_smallest(tableau[0].begin() + 1, tableau[0].end() - 1) >= 0 - EPSILON)
    {
        return true;
    }

    return false;
}

bool Simplex::CheckInfeasibility()
{
    return false;
}

void Simplex::CalculateSolution()
{
    int count = 0;
    for (int i : basic_variables)
    {
        solution[i] = tableau[count + 1][tableau[0].size() - 1] / tableau[count + 1][i + 1];
        count++;
    }
}

void Simplex::Solve()
{
    solution = std::vector<long double>(tableau[0].size() - 2, 0);

    while (true)
    {

        solution = std::vector<long double>(tableau[0].size() - 2, 0);
        //CalculateSolution();

        is_optimal = CheckOptimality();
        is_infeasible = CheckInfeasibility();

        if (is_optimal || is_infeasible)
            break;

        int j = FindPivotColumn();
        int i = FindPivotRow(j);

        std::cout << tableau[i][j] << "\n";

        basic_variables[i - 1] = j - 1;

        for (int m = 0; m < tableau.size(); m++)
        {
            if (m == i)
                continue;

            Pivot(m, i, j);
        }
    }
    CalculateSolution();
    objective_value = tableau[0][tableau[0].size() - 1];
}

std::string Simplex::ToString()
{
    std::string str = "";
    for (int i = 0; i < tableau.size(); i++)
    {
        for (int j = 0; j < tableau[i].size(); j++)
        {
            str += std::to_string(tableau[i][j]) + " ";
        }
        str += "\n";
    }
    str += "\n\n";
    for (int i = 0; i < solution.size(); i++)
    {
        str += std::to_string(solution[i]) + " ";
    }
    str += "\n\n\n";
    return str;
}

#endif