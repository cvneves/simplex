#include <iostream>
#include <fstream>
#include "Simplex.h"

int main()
{
    /*https://jaredantrobus.com/squirrel/2015/Summer/MA162/4.1.php*/
    /*http://simplex.tode.cz/en/#steps*/

    std::ifstream f;
    f.open("p11_converted.mps");
    std::string line;

    int i = 0;
    int j = 0;
    int n_columns, n_rows;
    std::vector<std::vector<double>> t;
    std::vector<int> basic_vars;

    if (f.is_open())
    {
        while (std::getline(f, line))
        {

            switch (i)
            {
            case 0:
                n_rows = std::stoi(line);
                break;
            case 1:
                n_columns = std::stoi(line);
                t = std::vector<std::vector<double>>(n_rows, std::vector<double>(n_columns));
                break;
            }

            if (i >= 2 && i <= (n_rows * n_columns + 1))
            {
                t[(i - 2) / n_columns][j] = std::stof(line);
                j++;
                if (j == n_columns)
                    j = 0;
            }

            if (i > (n_rows * n_columns + 2))
            {
                basic_vars.push_back(std::stoi(line));
            }

            i++;
        }

        f.close();

        Simplex a;

        a.tableau = t;
        a.basic_variables = basic_vars;
        a.Solve();
        std::cout << a.ToString();
    }
    else
        std::cout << "ERRO";
}