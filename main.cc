#include <iostream>
#include <fstream>
#include "Simplex.h"

int main(int argc, char* argv[])
{
    /*https://jaredantrobus.com/squirrel/2015/Summer/MA162/4.1.php*/
    /*http://simplex.tode.cz/en/#steps*/

    std::ifstream f;
    std::string file_name = argv[1];
    f.open(file_name);
    std::string line;

    int n_columns, n_rows;

    std::getline(f, line);
    n_rows = std::stoi(line);
    std::getline(f, line);
    n_columns = std::stoi(line);

    int i = 0;
    int j = 0;

    std::vector<std::vector<double>> t(n_rows, std::vector<double>(n_columns));

    while (std::getline(f, line) && i < n_rows * n_columns)
    {
        t[i / n_columns][j] = std::stof(line);

        j++;
        if (j == n_columns)
            j = 0;
        i++;
    }

    i = 0;

    std::vector<int> basic_vars(std::stoi(line));
    //std::cout << "  " << basic_vars.size() << "\n";

    for(int &i : basic_vars)
    {
        std::getline(f, line);
        i = std::stoi(line);
    }


    Simplex a;
    a.tableau = t;
    std::cout << a.ToString();
    a.basic_variables = basic_vars;
    a.Solve();
    std::cout << a.ToString();
}