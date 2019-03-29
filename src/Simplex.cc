#ifndef SIMPLEX_CC
#define SIMPLEX_CC

#include "Simplex.h"

int Simplex::FindPivotColumn()
{
    int j = min_element(tableau[0].begin() + 1, tableau[0].end()) - tableau[0].begin();
    return j;
}

int Simplex::FindPivotRow(int j)
{
    std::vector<double> v;
    for (int i = 1; i < tableau.size(); i++)
    {
        if (tableau[i][j] <= 0)
        {
            v.push_back(std::numeric_limits<double>::max());
            continue;
        }
        v.push_back(tableau[i][tableau[0].size() - 1] / tableau[i][j]);
    }

    int i = min_element(v.begin(), v.end()) - v.begin() + 1;
    return i;
}

void Simplex::Pivot(int r, int i, int j)
{
    std::vector<double> v = tableau[r];
    for (int n = 0; n < tableau[r].size(); n++)
    {
        v[n] = tableau[r][n] - tableau[r][j] * tableau[i][n] / tableau[i][j];
    }
    tableau[r] = v;
}

bool Simplex::CheckOptimality()
{
    if (*min_element(tableau[0].begin() + 1, tableau[0].end() - 1) >= 0)
        return true;
    return false;
}

bool Simplex::CheckInfeasibility()
{
    return false;
}

void Simplex::Solve()
{
    while (true)
    {
        is_optimal = CheckOptimality();
        is_infeasible = CheckInfeasibility();

        if (is_optimal || is_infeasible)
            break;

        int j = FindPivotColumn();
        int i = FindPivotRow(j);

        basic_variables[i - 1] = j - 1;

        for (int m = 0; m < tableau.size(); m++)
        {
            if (m == i)
                continue;

            Pivot(m, i, j);
        }
    }

    objective_value = tableau[0][tableau[0].size() - 1] / *tableau[0].begin();

    solution = std::vector<double>(tableau[0].size() - 2, 0);

    {
        int count = 0;
        for (int i : basic_variables)
        {
            solution[i] = tableau[count + 1][tableau[0].size() - 1] / tableau[count + 1][i + 1];
            count++;
        }
    }
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
    str += "\n";
    return str;
}

#endif